#include <gtest/gtest.h>
#include "Processor.h"
#include <thread>
#include <chrono>
#include <vector>
#include <future>

class MarketDataProcessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        processor = std::make_unique<MarketData::Processor>(2);  // Use just 2 threads for basic tests
        processor->start();
    }

    void TearDown() override {
        processor->stop();
    }

    std::unique_ptr<MarketData::Processor> processor;
};

// Test basic data addition and retrieval
TEST_F(MarketDataProcessorTest, BasicDataAddition) {
    processor->addData(MarketData::MarketData("AAPL", 150.0, 100));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    EXPECT_DOUBLE_EQ(processor->getLastPrice("AAPL"), 150.0);
    EXPECT_EQ(processor->getTotalVolume("AAPL"), 100);
}

// Test multiple data points for same symbol
TEST_F(MarketDataProcessorTest, MultipleUpdates) {
    processor->addData(MarketData::MarketData("AAPL", 150.0, 100));
    processor->addData(MarketData::MarketData("AAPL", 151.0, 200));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    EXPECT_DOUBLE_EQ(processor->getLastPrice("AAPL"), 151.0);
    EXPECT_EQ(processor->getTotalVolume("AAPL"), 300);
}

// Test non-existent symbol
TEST_F(MarketDataProcessorTest, NonExistentSymbol) {
    EXPECT_DOUBLE_EQ(processor->getLastPrice("NONEXISTENT"), 0.0);
    EXPECT_EQ(processor->getTotalVolume("NONEXISTENT"), 0);
}

TEST_F(MarketDataProcessorTest, MultipleSymbols) {
    // Add test data for multiple symbols
    processor->addData(MarketData::MarketData("AAPL", 150.0, 100));
    processor->addData(MarketData::MarketData("GOOGL", 2800.0, 50));
    processor->addData(MarketData::MarketData("MSFT", 300.0, 75));
    
    // Give some time for processing
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify results
    EXPECT_DOUBLE_EQ(processor->getLastPrice("AAPL"), 150.0);
    EXPECT_DOUBLE_EQ(processor->getLastPrice("GOOGL"), 2800.0);
    EXPECT_DOUBLE_EQ(processor->getLastPrice("MSFT"), 300.0);
    
    EXPECT_EQ(processor->getTotalVolume("AAPL"), 100);
    EXPECT_EQ(processor->getTotalVolume("GOOGL"), 50);
    EXPECT_EQ(processor->getTotalVolume("MSFT"), 75);
}

TEST_F(MarketDataProcessorTest, ConcurrentProcessing) {
    const int numThreads = 4;
    const int updatesPerThread = 1000;
    std::vector<std::future<void>> futures;
    
    // Create multiple threads updating the same symbol
    for (int i = 0; i < numThreads; ++i) {
        futures.push_back(std::async(std::launch::async, [this, i, updatesPerThread]() {
            for (int j = 0; j < updatesPerThread; ++j) {
                processor->addData(MarketData::MarketData("AAPL", 150.0 + i, 100));
            }
        }));
    }
    
    // Wait for all threads to complete
    for (auto& future : futures) {
        future.wait();
    }
    
    // Give some time for final processing
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify total volume
    EXPECT_EQ(processor->getTotalVolume("AAPL"), numThreads * updatesPerThread * 100);
}

TEST_F(MarketDataProcessorTest, StopAndStart) {
    // Add initial data
    processor->addData(MarketData::MarketData("AAPL", 150.0, 100));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_DOUBLE_EQ(processor->getLastPrice("AAPL"), 150.0);
    EXPECT_EQ(processor->getTotalVolume("AAPL"), 100);
    
    // Stop processing
    processor->stop();
    
    // Add more data while stopped (should be ignored)
    processor->addData(MarketData::MarketData("AAPL", 151.0, 200));
    
    // Start processing again
    processor->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // Verify state is unchanged
    EXPECT_DOUBLE_EQ(processor->getLastPrice("AAPL"), 150.0);
    EXPECT_EQ(processor->getTotalVolume("AAPL"), 100);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 