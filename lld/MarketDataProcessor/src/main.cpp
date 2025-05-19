#include "Processor.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Create a processor with 4 worker threads
    MarketData::Processor processor(4);
    
    // Start processing
    processor.start();
    
    // Add some test data
    processor.addData(MarketData::MarketData("AAPL", 150.0, 100));
    processor.addData(MarketData::MarketData("GOOGL", 2800.0, 50));
    processor.addData(MarketData::MarketData("AAPL", 151.0, 200));
    
    // Give some time for processing
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Print results
    std::cout << "AAPL Last Price: " << processor.getLastPrice("AAPL") << std::endl;
    std::cout << "AAPL Total Volume: " << processor.getTotalVolume("AAPL") << std::endl;
    std::cout << "GOOGL Last Price: " << processor.getLastPrice("GOOGL") << std::endl;
    std::cout << "GOOGL Total Volume: " << processor.getTotalVolume("GOOGL") << std::endl;
    
    // Stop processing
    processor.stop();
    
    return 0;
} 