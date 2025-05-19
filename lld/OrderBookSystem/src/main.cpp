#include "OrderBook.h"
#include <iostream>

int main() {
    OrderBook::OrderBook book;
    
    // Add some test orders
    book.addOrder(OrderBook::Order(100.0, 10, OrderBook::OrderType::BUY));
    book.addOrder(OrderBook::Order(99.0, 5, OrderBook::OrderType::SELL));
    
    // Match orders
    book.matchOrders();
    
    // Print order book snapshot
    auto snapshot = book.getOrderBookSnapshot();
    std::cout << "Order Book Snapshot:\n";
    for (const auto& [price, volume] : snapshot) {
        std::cout << "Price: " << price << ", Volume: " << volume << "\n";
    }
    
    return 0;
} 