#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include <atomic>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <array>
#include <thread>
#include <fstream>  // Added for file operations
#include "../include/WebpageCounter.h"
#include "../include/Logger.h"


// Custom exceptions
class InvalidPageIndex : public std::runtime_error {
public:
    explicit InvalidPageIndex(int index) 
        : std::runtime_error("Invalid page index: " + std::to_string(index)) {}
};

// Metrics implementation
Metrics::Metrics(const Metrics& other) {
    totalIncrements = other.totalIncrements.load(); // load from atomic struct to avoid race condition
    totalQueries = other.totalQueries.load(); // to safely read the value from atomic struct
    errorCount = other.errorCount.load();
}

Metrics& Metrics::operator=(const Metrics& other) {
    if (this != &other) {
        totalIncrements = other.totalIncrements.load();
        totalQueries = other.totalQueries.load();
        errorCount = other.errorCount.load();
    }
    return *this; // since return type is reference, we need to return the object as value not address
}

// WebpageCounter implementation
WebpageCounter::WebpageCounter(size_t totalPages, std::shared_ptr<ILogger> logger, const Config& config)
    : logger(std::move(logger))
    , totalPages(totalPages)
    , metrics()
    , config(config)
{
    std::cout << "Starting constructor initialization..." << std::endl;

    if (!this->logger) {
        throw std::invalid_argument("Logger cannot be null");
    }
    std::cout << "Logger validated..." << std::endl;

    if (totalPages <= 0) {
        throw std::invalid_argument("Total pages must be positive");
    }

    if (totalPages > MAX_PAGES) {
        throw std::invalid_argument("Total pages exceeds maximum allowed");
    }
    std::cout << "Bounds checking passed..." << std::endl;

    try {
        std::cout << "Starting array initialization..." << std::endl;
        
        for (size_t i = 0; i < totalPages; ++i) {
            std::cout << "Initializing page " << i << "..." << std::endl;
            
            try {
                visitCounts[i].store(0, std::memory_order_relaxed);
                std::cout << "Atomic initialized for page " << i << std::endl;
                
                mutexes[i] = std::make_unique<std::mutex>();
                if (!mutexes[i]) {
                    throw std::runtime_error("Failed to create mutex for page " + std::to_string(i));
                }
                std::cout << "Mutex created for page " << i << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error initializing page " << i << ": " << e.what() << std::endl;
                throw;
            }
        }

        for (size_t i = 0; i < totalPages; ++i) {
            if (!mutexes[i]) {
                throw std::runtime_error("Mutex verification failed for page " + std::to_string(i));
            }
            int count = visitCounts[i].load(std::memory_order_relaxed);
            if (count != 0) {
                throw std::runtime_error("Visit count verification failed for page " + std::to_string(i));
            }
        }
        std::cout << "Initialization verification passed" << std::endl;

        if (config.enableLogging) {
            this->logger->log("Initialized counter with " + std::to_string(totalPages) + " pages");
        }
        std::cout << "Constructor initialization completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception during initialization: " << e.what() << std::endl;
        throw std::runtime_error("Failed to initialize arrays: " + std::string(e.what()));
    }
}

void WebpageCounter::incrementVisitCount(size_t pageIndex) {
    if (pageIndex >= totalPages) {
        metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
        throw InvalidPageIndex(static_cast<int>(pageIndex));
    }

    if (config.useAtomicOperations) {
        visitCounts[pageIndex].fetch_add(1, std::memory_order_relaxed);
    } else {
        if (!mutexes[pageIndex]) {
            throw std::runtime_error("Mutex not initialized for page " + std::to_string(pageIndex));
        }
        std::lock_guard<std::mutex> lock(*mutexes[pageIndex]);
        visitCounts[pageIndex].store(visitCounts[pageIndex].load(std::memory_order_relaxed) + 1, std::memory_order_relaxed);
    }
    metrics.totalIncrements.fetch_add(1, std::memory_order_relaxed);
    
    if (config.enableLogging) {
        logger->log("Incremented visit count for page " + std::to_string(pageIndex));
    }
}

void WebpageCounter::batchIncrement(const std::vector<size_t>& indices) {
    if (indices.empty()) {
        return;
    }

    std::vector<size_t> sortedIndices = indices;
    std::sort(sortedIndices.begin(), sortedIndices.end());
    sortedIndices.erase(std::unique(sortedIndices.begin(), sortedIndices.end()), sortedIndices.end());
    
    std::vector<std::unique_lock<std::mutex>> locks;
    locks.reserve(sortedIndices.size());
    
    for (size_t index : sortedIndices) {
        if (index < 0 || index >= totalPages) {
            metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
            throw InvalidPageIndex(static_cast<int>(index));
        }
        if (!mutexes[index]) {
            throw std::runtime_error("Mutex not initialized for page " + std::to_string(index));
        }
        
        std::unique_lock<std::mutex> lock(*mutexes[index], std::try_to_lock);
        if (!lock.owns_lock()) {
            throw std::runtime_error("Failed to acquire lock for page " + std::to_string(index));
        }
        locks.push_back(std::move(lock));
    }
    
    for (size_t index : sortedIndices) {
        visitCounts[index].fetch_add(1, std::memory_order_relaxed);
        metrics.totalIncrements.fetch_add(1, std::memory_order_relaxed);
    }
    
    if (config.enableLogging) {
        logger->log("Batch incremented " + std::to_string(sortedIndices.size()) + " pages");
    }
}

size_t WebpageCounter::getVisitCount(size_t pageIndex) const {
    if (pageIndex >= totalPages) {
        metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
        throw InvalidPageIndex(static_cast<int>(pageIndex));
    }

    int count;
    if (config.useAtomicOperations) {
        count = visitCounts[pageIndex].load(std::memory_order_relaxed);
    } else {
        if (!mutexes[pageIndex]) {
            throw std::runtime_error("Mutex not initialized for page " + std::to_string(pageIndex));
        }
        std::lock_guard<std::mutex> lock(*mutexes[pageIndex]);
        count = visitCounts[pageIndex].load(std::memory_order_relaxed);
    }
    
    metrics.totalQueries.fetch_add(1, std::memory_order_relaxed);
    
    if (config.enableLogging) {
        logger->log("Retrieved visit count for page " + std::to_string(pageIndex) + ": " + std::to_string(count));
    }
    
    return count;
}

Metrics WebpageCounter::getMetrics() const {
    return metrics;
}

void WebpageCounter::reset() {
    std::vector<std::unique_lock<std::mutex>> locks;
    locks.reserve(totalPages);
    
    for (size_t i = 0; i < totalPages; ++i) {
        if (!mutexes[i]) {
            throw std::runtime_error("Mutex not initialized for page " + std::to_string(i));
        }
        locks.emplace_back(*mutexes[i]);
        visitCounts[i].store(0, std::memory_order_relaxed);
    }
    
    metrics = Metrics{};
    if (config.enableLogging) {
        logger->log("Reset all counters");
    }
}
