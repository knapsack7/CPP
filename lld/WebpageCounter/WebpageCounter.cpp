#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include <atomic>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <array>

// Custom exceptions
class InvalidPageIndex : public std::runtime_error {
public:
    explicit InvalidPageIndex(int index) 
        : std::runtime_error("Invalid page index: " + std::to_string(index)) {}
};

// Configuration structure
struct Config {
    bool enableLogging = true;
    bool useAtomicOperations = false;
    size_t maxPages = 1000;
};

// Metrics structure
struct Metrics {
    std::atomic<size_t> totalIncrements{0};
    std::atomic<size_t> totalQueries{0};
    std::atomic<size_t> errorCount{0};

    // Add copy constructor and assignment operator
    Metrics() = default;
    Metrics(const Metrics& other) {
        totalIncrements = other.totalIncrements.load();
        totalQueries = other.totalQueries.load();
        errorCount = other.errorCount.load();
    }
    Metrics& operator=(const Metrics& other) {
        if (this != &other) {
            totalIncrements = other.totalIncrements.load();
            totalQueries = other.totalQueries.load();
            errorCount = other.errorCount.load();
        }
        return *this;
    }
};

// Logger interface
class ILogger {
public:
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

// Concrete Logger implementation
class Logger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

// Main WebpageCounter class
class WebpageCounter {
private:
    static constexpr size_t MAX_PAGES = 1000;
    std::array<std::atomic<int>, MAX_PAGES> visitCounts;
    std::array<std::unique_ptr<std::mutex>, MAX_PAGES> mutexes;
    std::unique_ptr<ILogger> logger;  // Keep the unique_ptr
    int totalPages;
    mutable Metrics metrics;
    Config config;

public:
    // Constructor instead of init method
    WebpageCounter(int totalPages, std::unique_ptr<ILogger> logger, const Config& config = Config{})
        : totalPages(totalPages)
        , logger(std::move(logger))  // Move the logger
        , config(config)
        , metrics()
    {
        std::cout << "Starting constructor initialization..." << std::endl;

        // Explicit logger validation
        if (!this->logger) {
            throw std::invalid_argument("Logger cannot be null");
        }
        std::cout << "Logger validated..." << std::endl;

        // Stricter bounds checking
        if (totalPages <= 0) {
            throw std::invalid_argument("Total pages must be positive");
        }

        if (static_cast<size_t>(totalPages) > MAX_PAGES) {
            throw std::invalid_argument("Total pages exceeds maximum allowed");
        }
        std::cout << "Bounds checking passed..." << std::endl;

        try {
            std::cout << "Starting array initialization..." << std::endl;
            
            // Initialize visit counts and create mutexes
            for (int i = 0; i < totalPages; ++i) {
                std::cout << "Initializing page " << i << "..." << std::endl;
                
                try {
                    // Initialize atomic with 0
                    visitCounts[i].store(0, std::memory_order_relaxed);
                    std::cout << "Atomic initialized for page " << i << std::endl;
                    
                    // Create mutex
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

            // Verify initialization
            for (int i = 0; i < totalPages; ++i) {
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

    // Single page increment
    void incrementVisitCount(int pageIndex) {
        if (pageIndex < 0 || pageIndex >= totalPages) {
            metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
            throw InvalidPageIndex(pageIndex);
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

    // Batch increment
    void batchIncrement(const std::vector<int>& indices) {
        if (indices.empty()) {
            return;
        }

        // Sort indices to prevent deadlock
        std::vector<int> sortedIndices = indices;
        std::sort(sortedIndices.begin(), sortedIndices.end());
        
        // Remove duplicates to avoid locking the same mutex twice
        sortedIndices.erase(std::unique(sortedIndices.begin(), sortedIndices.end()), sortedIndices.end());
        
        // Create a vector of unique_locks
        std::vector<std::unique_lock<std::mutex>> locks;
        locks.reserve(sortedIndices.size());
        
        // Try to acquire all locks
        for (int index : sortedIndices) {
            if (index < 0 || index >= totalPages) {
                metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
                throw InvalidPageIndex(index);
            }
            if (!mutexes[index]) {
                throw std::runtime_error("Mutex not initialized for page " + std::to_string(index));
            }
            
            // Try to acquire the lock with a timeout
            std::unique_lock<std::mutex> lock(*mutexes[index], std::try_to_lock);
            if (!lock.owns_lock()) {
                throw std::runtime_error("Failed to acquire lock for page " + std::to_string(index));
            }
            locks.push_back(std::move(lock));
        }
        
        // All locks acquired, perform the increments
        for (int index : sortedIndices) {
            visitCounts[index].fetch_add(1, std::memory_order_relaxed);
            metrics.totalIncrements.fetch_add(1, std::memory_order_relaxed);
        }
        
        if (config.enableLogging) {
            logger->log("Batch incremented " + std::to_string(sortedIndices.size()) + " pages");
        }
    }

    // Get visit count
    int getVisitCount(int pageIndex) const {
        if (pageIndex < 0 || pageIndex >= totalPages) {
            metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
            throw InvalidPageIndex(pageIndex);
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

    // Get metrics
    Metrics getMetrics() const {
        return metrics;
    }

    // Reset counters (for testing)
    void reset() {
        // Lock all mutexes before resetting
        std::vector<std::unique_lock<std::mutex>> locks;
        locks.reserve(totalPages);
        
        for (int i = 0; i < totalPages; ++i) {
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
};

// Example usage
int main() {
    try {
        std::cout << "Starting WebpageCounter Test..." << std::endl;

        Config config;
        config.enableLogging = true;
        config.useAtomicOperations = true;
        std::cout << "Configuration set: Logging enabled, Atomic operations enabled" << std::endl;

        std::cout << "Creating logger..." << std::endl;
        auto logger = std::make_unique<Logger>();
        if (!logger) {
            throw std::runtime_error("Failed to create logger");
        }

        std::cout << "Initializing WebpageCounter with 2 pages..." << std::endl;
        WebpageCounter counter(2, std::move(logger), config);
        std::cout << "WebpageCounter initialized successfully" << std::endl;
        
        std::cout << "Performing single page increments..." << std::endl;
        counter.incrementVisitCount(0);
        std::cout << "Incremented page 0" << std::endl;
        counter.incrementVisitCount(1);
        std::cout << "Incremented page 1" << std::endl;
        
        std::cout << "Performing batch increment..." << std::endl;
        std::vector<int> batchIndices = {1, 1, 0};
        counter.batchIncrement(batchIndices);
        std::cout << "Batch increment completed" << std::endl;
        
        std::cout << "Retrieving visit counts..." << std::endl;
        int count0 = counter.getVisitCount(0);
        std::cout << "Page 0 visits: " << count0 << std::endl;
        int count1 = counter.getVisitCount(1);
        std::cout << "Page 1 visits: " << count1 << std::endl;
        
        std::cout << "Retrieving metrics..." << std::endl;
        auto metrics = counter.getMetrics();
        std::cout << "Total increments: " << metrics.totalIncrements << std::endl;
        std::cout << "Total queries: " << metrics.totalQueries << std::endl;
        std::cout << "Error count: " << metrics.errorCount << std::endl;
        
        std::cout << "WebpageCounter Test Completed Successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Unhandled Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown Exception Occurred" << std::endl;
        return 2;
    }
    
    return 0;
}
