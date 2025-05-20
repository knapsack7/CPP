#include <gtest/gtest.h>
#include "Client.h"
#include "MarketDataStream.h"
#include "Server.h"
#include <chrono>
#include <thread>

using namespace TradingSystem;

class TradingCasesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize components
        marketDataStream = std::make_unique<MarketDataStream>();
        server = std::make_unique<Server>("127.0.0.1", 8080);
        
        // Start services
        marketDataStream->start();
        server->start();
        
        // Wait for server to be ready
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void TearDown() override {
        // Stop services
        server->stop();
        marketDataStream->stop();
        
        // Cleanup
        server.reset();
        marketDataStream.reset();
    }

    // Helper methods
    std::unique_ptr<Client> createAndConnectClient() {
        auto client = std::make_unique<Client>("127.0.0.1", "8080");
        client->start();
        EXPECT_TRUE(client->login("test_user", "test_pass"));
        return client;
    }

    std::unique_ptr<MarketDataStream> marketDataStream;
    std::unique_ptr<Server> server;
};

TEST_F(TradingCasesTest, PlaceOrder) {
    auto client = createAndConnectClient();
    
    // Test buy order
    EXPECT_TRUE(client->placeOrder("AAPL", 150.0, 10, trading::OrderSide::BUY));
    
    // Test sell order
    EXPECT_TRUE(client->placeOrder("AAPL", 151.0, 5, trading::OrderSide::SELL));
}

TEST_F(TradingCasesTest, CancelOrder) {
    auto client = createAndConnectClient();
    
    // Place and cancel order
    EXPECT_TRUE(client->placeOrder("AAPL", 150.0, 10, trading::OrderSide::BUY));
    EXPECT_TRUE(client->cancelOrder("order1"));
}

TEST_F(TradingCasesTest, MarketDataSubscription) {
    auto client = createAndConnectClient();
    
    // Subscribe to market data
    EXPECT_TRUE(client->subscribeMarketData("AAPL", trading::MarketDataType::TRADE));
    EXPECT_TRUE(client->subscribeMarketData("AAPL", trading::MarketDataType::QUOTE));
    
    // Unsubscribe
    EXPECT_TRUE(client->unsubscribeMarketData("AAPL", trading::MarketDataType::TRADE));
} 