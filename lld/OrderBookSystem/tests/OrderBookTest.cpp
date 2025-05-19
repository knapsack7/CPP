#include <gtest/gtest.h>
#include "OrderBook.h"
#include "MarketData.h"
#include <iostream>

class OrderBookTest : public ::testing::Test {
protected:
    OrderBook::OrderBook book;
    OrderBook::MarketData marketData;
};

TEST_F(OrderBookTest, BasicOrderMatching) {
    // Add a buy order
    book.addOrder(OrderBook::Order(100.0, 10, OrderBook::OrderType::BUY));
    
    // Add a matching sell order
    book.addOrder(OrderBook::Order(99.0, 5, OrderBook::OrderType::SELL));
    
    // Match orders
    book.matchOrders();
    
    // Verify the remaining quantities
    EXPECT_EQ(book.getVolumeAtPrice(100.0), 5);  // Remaining buy order
    EXPECT_EQ(book.getVolumeAtPrice(99.0), 0);   // Sell order should be fully matched
}

TEST_F(OrderBookTest, PriceTimePriority) {
    // Add multiple buy orders at the same price
    book.addOrder(OrderBook::Order(100.0, 5, OrderBook::OrderType::BUY));   // First order
    book.addOrder(OrderBook::Order(100.0, 3, OrderBook::OrderType::BUY));   // Second order
    
    // Add a matching sell order
    book.addOrder(OrderBook::Order(99.0, 7, OrderBook::OrderType::SELL));
    
    // Match orders
    book.matchOrders();
    
    // Verify that the first buy order is matched first
    EXPECT_EQ(book.getVolumeAtPrice(100.0), 1);  // 5 + 3 - 7 = 1 remaining
}

TEST_F(OrderBookTest, MarketDataRecording) {
    // Add and match some orders
    book.addOrder(OrderBook::Order(100.0, 10, OrderBook::OrderType::BUY));
    book.addOrder(OrderBook::Order(99.0, 5, OrderBook::OrderType::SELL));
    book.matchOrders();
    
    // Record the trade
    OrderBook::Trade trade{
        "buy-order-1",
        "sell-order-1",
        99.5,  // Mid price
        5,     // Quantity
        std::chrono::system_clock::now()
    };
    marketData.recordTrade(trade);
    
    // Verify market data
    EXPECT_EQ(marketData.getLastTradePrice(), 99.5);
    EXPECT_EQ(marketData.getVolumeInLastMinute(), 5);
}

TEST_F(OrderBookTest, BestBidAsk) {
    // Add orders at different price levels
    book.addOrder(OrderBook::Order(100.0, 5, OrderBook::OrderType::BUY));   // Best bid
    book.addOrder(OrderBook::Order(99.0, 5, OrderBook::OrderType::BUY));    // Lower bid
    book.addOrder(OrderBook::Order(101.0, 5, OrderBook::OrderType::SELL));  // Best ask
    book.addOrder(OrderBook::Order(102.0, 5, OrderBook::OrderType::SELL));  // Higher ask
    
    EXPECT_EQ(book.getBestBid(), 100.0);
    EXPECT_EQ(book.getBestAsk(), 101.0);
}

TEST_F(OrderBookTest, OrderBookSnapshot) {
    // Add orders at different price levels
    book.addOrder(OrderBook::Order(100.0, 5, OrderBook::OrderType::BUY));
    book.addOrder(OrderBook::Order(101.0, 3, OrderBook::OrderType::SELL));
    
    auto snapshot = book.getOrderBookSnapshot();
    
    // Verify snapshot contains correct price levels and volumes
    bool foundBid = false;
    bool foundAsk = false;
    
    for (const auto& [price, volume] : snapshot) {
        if (price == 100.0) {
            EXPECT_EQ(volume, 5);
            foundBid = true;
        }
        if (price == 101.0) {
            EXPECT_EQ(volume, 3);
            foundAsk = true;
        }
    }
    
    EXPECT_TRUE(foundBid);
    EXPECT_TRUE(foundAsk);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 