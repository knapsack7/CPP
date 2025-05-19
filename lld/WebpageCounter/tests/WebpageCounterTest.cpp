#include "../include/WebpageCounter.h"
#include "../include/Logger.h"
#include <iostream>
#include <thread>
#include <vector>

void runSingleThreadTest(WebpageCounter& counter) {
    std::cout << "\nTest Case 1: Single thread operations" << std::endl;
    counter.incrementVisitCount(0);
    counter.incrementVisitCount(1);
    std::cout << "Page 0 visits: " << counter.getVisitCount(0) << std::endl;
    std::cout << "Page 1 visits: " << counter.getVisitCount(1) << std::endl;
    
    std::cout << "\nResetting counters..." << std::endl;
    counter.reset();
    std::cout << "After reset - Page 0 visits: " << counter.getVisitCount(0) << std::endl;
    std::cout << "After reset - Page 1 visits: " << counter.getVisitCount(1) << std::endl;
}

void runMultiThreadTest(WebpageCounter& counter) {
    std::cout << "\nTest Case 2: Multithreaded operations" << std::endl;
    std::vector<std::thread> threads;
    const int numThreads = 4;
    const int incrementsPerThread = 1000;

    std::cout << "Starting " << numThreads << " threads, each performing " 
              << incrementsPerThread << " increments..." << std::endl;

    // Create threads for page 0
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.incrementVisitCount(0);
            }
        });
    }

    // Create threads for page 1
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.incrementVisitCount(1);
            }
        });
    }

    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "All threads completed" << std::endl;
    
    // Verify results
    std::cout << "Retrieving visit counts..." << std::endl;
    int count0 = counter.getVisitCount(0);
    std::cout << "Page 0 visits: " << count0 << std::endl;
    int count1 = counter.getVisitCount(1);
    std::cout << "Page 1 visits: " << count1 << std::endl;
    
    // Check metrics
    std::cout << "Retrieving metrics..." << std::endl;
    auto metrics = counter.getMetrics();
    std::cout << "Total increments: " << metrics.totalIncrements << std::endl;
    std::cout << "Total queries: " << metrics.totalQueries << std::endl;
    std::cout << "Error count: " << metrics.errorCount << std::endl;
}

int main() {
    try {
        std::cout << "Starting WebpageCounter Test..." << std::endl;

        // Configure the counter
        Config config;
        config.enableLogging = true;
        config.useAtomicOperations = true;
        std::cout << "Configuration set: Logging enabled, Atomic operations enabled" << std::endl;

        // Initialize logger
        std::cout << "Creating logger..." << std::endl;
        auto logger = Logger::getInstance();
        if (!logger) {
            throw std::runtime_error("Failed to create logger");
        }

        // Create counter
        std::cout << "Initializing WebpageCounter with 2 pages..." << std::endl;
        WebpageCounter counter(2, std::move(logger), config);
        std::cout << "WebpageCounter initialized successfully" << std::endl;
        
        // Run tests
        runSingleThreadTest(counter);
        runMultiThreadTest(counter);
        
        // Final reset and check
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