#include <gtest/gtest.h>
#include "RiskManager.h"
#include <iostream>

namespace TradingSystem {
namespace {

class RiskManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up some test limits
        risk_manager_.setPositionLimit("client1", "AAPL", 1000);
        risk_manager_.setPositionLimit("client1", "GOOGL", 500);
        risk_manager_.setPriceLimit("AAPL", 100.0, 200.0);
        risk_manager_.setPriceLimit("GOOGL", 2000.0, 3000.0);
        risk_manager_.setDailyLimit("client1", 100000.0);
    }

    RiskManager risk_manager_;
};

TEST_F(RiskManagerTest, ValidOrder) {
    std::cout << "Testing valid order validation..." << std::endl;
    trading::Order order;
    order.set_client_id("client1");
    order.set_symbol("AAPL");
    order.set_quantity(100);
    order.set_price(150.0);
    
    EXPECT_TRUE(risk_manager_.validateOrder(order));
    std::cout << "Valid order test passed." << std::endl;
}

TEST_F(RiskManagerTest, InvalidPositionLimit) {
    std::cout << "Testing invalid position limit..." << std::endl;
    trading::Order order;
    order.set_client_id("client1");
    order.set_symbol("AAPL");
    order.set_quantity(2000);  // Exceeds position limit of 1000
    order.set_price(150.0);
    
    EXPECT_FALSE(risk_manager_.validateOrder(order));
    std::cout << "Invalid position limit test passed." << std::endl;
}

TEST_F(RiskManagerTest, InvalidPriceLimit) {
    std::cout << "Testing invalid price limit..." << std::endl;
    trading::Order order;
    order.set_client_id("client1");
    order.set_symbol("AAPL");
    order.set_quantity(100);
    order.set_price(50.0);  // Below minimum price of 100.0
    
    EXPECT_FALSE(risk_manager_.validateOrder(order));
    std::cout << "Invalid price limit test passed." << std::endl;
}

TEST_F(RiskManagerTest, InvalidDailyLimit) {
    std::cout << "Testing invalid daily limit..." << std::endl;
    trading::Order order;
    order.set_client_id("client1");
    order.set_symbol("AAPL");
    order.set_quantity(1000);
    order.set_price(150.0);  // Total value: 150,000 (exceeds daily limit of 100,000)
    
    EXPECT_FALSE(risk_manager_.validateOrder(order));
    std::cout << "Invalid daily limit test passed." << std::endl;
}

TEST_F(RiskManagerTest, PositionTracking) {
    std::cout << "Testing position tracking..." << std::endl;
    // Place initial order
    trading::Order order1;
    order1.set_client_id("client1");
    order1.set_symbol("AAPL");
    order1.set_quantity(500);
    order1.set_price(150.0);
    
    EXPECT_TRUE(risk_manager_.validateOrder(order1));
    risk_manager_.updatePosition("client1", "AAPL", 500);
    
    // Try to place another order that would exceed limit
    trading::Order order2;
    order2.set_client_id("client1");
    order2.set_symbol("AAPL");
    order2.set_quantity(600);  // Would exceed limit of 1000
    order2.set_price(150.0);
    
    EXPECT_FALSE(risk_manager_.validateOrder(order2));
    
    // Verify current position
    EXPECT_EQ(risk_manager_.getPosition("client1", "AAPL"), 500);
    std::cout << "Position tracking test passed." << std::endl;
}

TEST_F(RiskManagerTest, MultipleSymbols) {
    std::cout << "Testing multiple symbols..." << std::endl;
    // Place orders for different symbols
    trading::Order order1;
    order1.set_client_id("client1");
    order1.set_symbol("AAPL");
    order1.set_quantity(500);
    order1.set_price(150.0);
    
    trading::Order order2;
    order2.set_client_id("client1");
    order2.set_symbol("GOOGL");
    order2.set_quantity(200);
    order2.set_price(2500.0);
    
    EXPECT_TRUE(risk_manager_.validateOrder(order1));
    risk_manager_.updateDailyTotal("client1", 500 * 150.0);
    EXPECT_FALSE(risk_manager_.validateOrder(order2)); // Should fail due to daily limit
    
    risk_manager_.updatePosition("client1", "AAPL", 500);
    risk_manager_.updatePosition("client1", "GOOGL", 200);
    
    // Verify positions for both symbols
    EXPECT_EQ(risk_manager_.getPosition("client1", "AAPL"), 500);
    EXPECT_EQ(risk_manager_.getPosition("client1", "GOOGL"), 200);
    std::cout << "Multiple symbols test passed." << std::endl;
}

TEST_F(RiskManagerTest, UnknownSymbol) {
    std::cout << "Testing unknown symbol..." << std::endl;
    trading::Order order;
    order.set_client_id("client1");
    order.set_symbol("UNKNOWN");
    order.set_quantity(100);
    order.set_price(150.0);
    
    // Should pass validation as no limits are set for unknown symbol
    EXPECT_TRUE(risk_manager_.validateOrder(order));
    std::cout << "Unknown symbol test passed." << std::endl;
}

TEST_F(RiskManagerTest, UnknownClient) {
    std::cout << "Testing unknown client..." << std::endl;
    trading::Order order;
    order.set_client_id("unknown_client");
    order.set_symbol("AAPL");
    order.set_quantity(100);
    order.set_price(150.0);
    
    // Should pass validation as no limits are set for unknown client
    EXPECT_TRUE(risk_manager_.validateOrder(order));
    std::cout << "Unknown client test passed." << std::endl;
}

} // namespace
} // namespace TradingSystem 