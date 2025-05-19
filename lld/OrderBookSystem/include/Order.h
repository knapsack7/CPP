#pragma once

#include <string>
#include <chrono>
#include <memory>

namespace OrderBook {

enum class OrderType {
    BUY,
    SELL
};

class Order {
public:
    Order(double price, int quantity, OrderType type);
    
    // Getters
    double getPrice() const { return price_; }
    int getQuantity() const { return quantity_; }
    OrderType getType() const { return type_; }
    const std::string& getOrderId() const { return orderId_; }
    const std::chrono::system_clock::time_point& getTimestamp() const { return timestamp_; }

    // Setters
    void setQuantity(int quantity) { quantity_ = quantity; }

private:
    double price_;
    int quantity_;
    OrderType type_;
    std::string orderId_;
    std::chrono::system_clock::time_point timestamp_;

    // Helper function to generate unique order ID
    static std::string generateOrderId();
};

} // namespace OrderBook 