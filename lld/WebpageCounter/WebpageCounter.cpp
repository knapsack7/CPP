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
    // atomic is thread-safe when different threads are accessing the same object
    std::atomic<size_t> totalIncrements{0};
    std::atomic<size_t> totalQueries{0};
    std::atomic<size_t> errorCount{0};

    // Add copy constructor and assignment operator
    Metrics() = default;
    Metrics(const Metrics& other) {
        totalIncrements = other.totalIncrements.load(); // load from atomic struct to avoid race condition
        totalQueries = other.totalQueries.load(); // to safely read the value from atomic struct
        errorCount = other.errorCount.load();
    }
    Metrics& operator=(const Metrics& other) {
        if (this != &other) {
            totalIncrements = other.totalIncrements.load();
            totalQueries = other.totalQueries.load();
            errorCount = other.errorCount.load();
        }
        return *this; // since return type is reference, we need to return the object as value not address
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
private:
    static std::shared_ptr<Logger> instance;
    static std::ofstream logFile;
    static std::mutex logMutex;

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    
public:
    static std::shared_ptr<Logger> getInstance() {
        if (!instance) {
            instance = std::shared_ptr<Logger>(new Logger());
        }
        return instance;
    }
    
    void log(const std::string& message) override {
        std::lock_guard<std::mutex> lock(logMutex);
        if (!logFile.is_open()) {
            logFile.open("log.txt", std::ios::out);  // Open in write mode
        }
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.flush();  // Ensure immediate writing
        }
    }
};

// Initialize static members
std::shared_ptr<Logger> Logger::instance = nullptr;
std::ofstream Logger::logFile;
std::mutex Logger::logMutex;

// Main WebpageCounter class
class WebpageCounter {
private:
    static constexpr size_t MAX_PAGES = 1000; // modern c++ style to use constexpr to inline define MAX_PAGES static member
    std::array<std::atomic<size_t>, MAX_PAGES> visitCounts;
    std::array<std::unique_ptr<std::mutex>, MAX_PAGES> mutexes;
    std::shared_ptr<ILogger> logger;  // Changed to shared_ptr
    size_t totalPages;
    mutable Metrics metrics;
    Config config;

public:
    // Constructor instead of init method
    // if no config is provided, it will use the default config
    WebpageCounter(size_t totalPages, std::shared_ptr<ILogger> logger, const Config& config = Config{})
        : totalPages(totalPages)
        , logger(std::move(logger))  // Move the logger
        , config(config)
        , metrics()  // default initialize metrics
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

        if (totalPages > MAX_PAGES) {
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
            // increment the error count
            metrics.errorCount.fetch_add(1, std::memory_order_relaxed);
            throw InvalidPageIndex(pageIndex);
        }

        if (config.useAtomicOperations) {
            visitCounts[pageIndex].fetch_add(1, std::memory_order_relaxed);
        } else { // if not using atomic operations, we need to lock the mutex
            if (!mutexes[pageIndex]) {
                throw std::runtime_error("Mutex not initialized for page " + std::to_string(pageIndex));
            }
            std::lock_guard<std::mutex> lock(*mutexes[pageIndex]);
            visitCounts[pageIndex].store(visitCounts[pageIndex].load(std::memory_order_relaxed) + 1, std::memory_order_relaxed);
        }
        // increment the total increments
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
        // Locks are automatically released when 'locks' vector goes out of scope
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
        auto logger = Logger::getInstance();  // Get singleton instance as shared_ptr
        if (!logger) {
            throw std::runtime_error("Failed to create logger");
        }

        std::cout << "Initializing WebpageCounter with 2 pages..." << std::endl;
        WebpageCounter counter(2, std::move(logger), config);
        std::cout << "WebpageCounter initialized successfully" << std::endl;
        
        // Test Case 1: Single thread operations
        std::cout << "\nTest Case 1: Single thread operations" << std::endl;
        counter.incrementVisitCount(0);
        counter.incrementVisitCount(1);
        std::cout << "Page 0 visits: " << counter.getVisitCount(0) << std::endl;
        std::cout << "Page 1 visits: " << counter.getVisitCount(1) << std::endl;
        
        std::cout << "\nResetting counters..." << std::endl;
        counter.reset();
        std::cout << "After reset - Page 0 visits: " << counter.getVisitCount(0) << std::endl;
        std::cout << "After reset - Page 1 visits: " << counter.getVisitCount(1) << std::endl;
        
        // Test Case 2: Multithreaded operations
        std::cout << "\nTest Case 2: Multithreaded operations" << std::endl;
        std::vector<std::thread> threads;
        const int numThreads = 4;
        const int incrementsPerThread = 1000;

        std::cout << "Starting " << numThreads << " threads, each performing " 
                  << incrementsPerThread << " increments..." << std::endl;

        // Create threads that will concurrently increment page 0
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([&counter, incrementsPerThread]() {
                for (int j = 0; j < incrementsPerThread; ++j) {
                    counter.incrementVisitCount(0);
                }
            });
        }

        // Create threads that will concurrently increment page 1
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([&counter, incrementsPerThread]() {
                for (int j = 0; j < incrementsPerThread; ++j) {
                    counter.incrementVisitCount(1);
                }
            });
        }

        // Wait for all threads to complete
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "All threads completed" << std::endl;
        
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
        
        std::cout << "\nResetting counters again..." << std::endl;
        counter.reset();
        std::cout << "Final check after reset - Page 0 visits: " << counter.getVisitCount(0) << std::endl;
        std::cout << "Final check after reset - Page 1 visits: " << counter.getVisitCount(1) << std::endl;
        
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
