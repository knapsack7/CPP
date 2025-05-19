#include "../include/WebpageCounter.h"
#include "../include/Logger.h"
#include <iostream>

int main() {
    try {
        // Configure the counter
        Config config;
        config.enableLogging = true;
        config.useAtomicOperations = true;

        // Initialize logger
        auto logger = Logger::getInstance();
        if (!logger) {
            throw std::runtime_error("Failed to create logger");
        }

        // Create counter with 3 pages
        WebpageCounter counter(3, std::move(logger), config);
        
        // Example usage
        std::cout << "Incrementing page visits..." << std::endl;
        counter.incrementVisitCount(0);
        counter.incrementVisitCount(1);
        counter.incrementVisitCount(2);
        
        // Batch increment
        std::vector<size_t> pages = {0, 1, 2};
        counter.batchIncrement(pages);
        
        // Display results
        std::cout << "\nVisit counts:" << std::endl;
        std::cout << "Page 0: " << counter.getVisitCount(0) << std::endl;
        std::cout << "Page 1: " << counter.getVisitCount(1) << std::endl;
        std::cout << "Page 2: " << counter.getVisitCount(2) << std::endl;
        
        // Show metrics
        auto metrics = counter.getMetrics();
        std::cout << "\nMetrics:" << std::endl;
        std::cout << "Total increments: " << metrics.totalIncrements << std::endl;
        std::cout << "Total queries: " << metrics.totalQueries << std::endl;
        std::cout << "Error count: " << metrics.errorCount << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 