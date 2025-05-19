#pragma once

#include "Order.h"
#include <map>
#include <queue>
#include <memory>
#include <vector>

namespace OrderBook {

class OrderBook {
public:
    OrderBook() = default;
    ~OrderBook() = default;

    // Prevent copying
    OrderBook(const OrderBook&) = delete;
    OrderBook& operator=(const OrderBook&) = delete;

    // Allow moving
    OrderBook(OrderBook&&) = default;
    OrderBook& operator=(OrderBook&&) = default;

    // Core functionality
    void addOrder(Order order);
    void matchOrders();
    
    // Market data
    double getBestBid() const;
    double getBestAsk() const;
    int getVolumeAtPrice(double price) const;
    std::vector<std::pair<double, int>> getOrderBookSnapshot() const;

private:
    // Price levels for buy and sell orders
    std::map<double, std::queue<std::unique_ptr<Order>>, std::greater<double>> buyOrders_;
    std::map<double, std::queue<std::unique_ptr<Order>>> sellOrders_;
    
    // Volume tracking
    std::map<double, int> buyVolumes_;
    std::map<double, int> sellVolumes_;

    // Helper functions
    bool canMatch(const Order& buy, const Order& sell) const;
    void executeTrade(Order& buy, Order& sell);
    void removeEmptyPriceLevels();
    void updateVolume(double price, int quantity, OrderType type);
};

} // namespace OrderBook 