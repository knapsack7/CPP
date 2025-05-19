#include "OrderBook.h"
#include <algorithm>
#include <stdexcept>

namespace OrderBook {

void OrderBook::addOrder(Order order) {
    auto orderPtr = std::make_unique<Order>(std::move(order));
    double price = orderPtr->getPrice();
    int quantity = orderPtr->getQuantity();
    OrderType type = orderPtr->getType();
    
    if (type == OrderType::BUY) {
        buyOrders_[price].push(std::move(orderPtr));
        buyVolumes_[price] += quantity;
    } else {
        sellOrders_[price].push(std::move(orderPtr));
        sellVolumes_[price] += quantity;
    }
}

void OrderBook::matchOrders() {
    while (!buyOrders_.empty() && !sellOrders_.empty()) {
        auto& bestBid = buyOrders_.begin()->second.front();
        auto& bestAsk = sellOrders_.begin()->second.front();
        
        if (!canMatch(*bestBid, *bestAsk)) {
            break;
        }
        
        executeTrade(*bestBid, *bestAsk);
        removeEmptyPriceLevels();
    }
}

bool OrderBook::canMatch(const Order& buy, const Order& sell) const {
    return buy.getPrice() >= sell.getPrice();
}

void OrderBook::executeTrade(Order& buy, Order& sell) {
    int tradeQuantity = std::min(buy.getQuantity(), sell.getQuantity());
    double buyPrice = buy.getPrice();
    double sellPrice = sell.getPrice();
    
    buy.setQuantity(buy.getQuantity() - tradeQuantity);
    sell.setQuantity(sell.getQuantity() - tradeQuantity);
    
    updateVolume(buyPrice, -tradeQuantity, OrderType::BUY);
    updateVolume(sellPrice, -tradeQuantity, OrderType::SELL);
    
    if (buy.getQuantity() == 0) {
        buyOrders_.begin()->second.pop();
    }
    if (sell.getQuantity() == 0) {
        sellOrders_.begin()->second.pop();
    }
}

void OrderBook::updateVolume(double price, int quantity, OrderType type) {
    if (type == OrderType::BUY) {
        buyVolumes_[price] += quantity;
        if (buyVolumes_[price] == 0) {
            buyVolumes_.erase(price);
        }
    } else {
        sellVolumes_[price] += quantity;
        if (sellVolumes_[price] == 0) {
            sellVolumes_.erase(price);
        }
    }
}

void OrderBook::removeEmptyPriceLevels() {
    for (auto it = buyOrders_.begin(); it != buyOrders_.end();) {
        if (it->second.empty()) {
            it = buyOrders_.erase(it);
        } else {
            ++it;
        }
    }
    
    for (auto it = sellOrders_.begin(); it != sellOrders_.end();) {
        if (it->second.empty()) {
            it = sellOrders_.erase(it);
        } else {
            ++it;
        }
    }
}

double OrderBook::getBestBid() const {
    if (buyOrders_.empty()) {
        throw std::runtime_error("No buy orders in the book");
    }
    return buyOrders_.begin()->first;
}

double OrderBook::getBestAsk() const {
    if (sellOrders_.empty()) {
        throw std::runtime_error("No sell orders in the book");
    }
    return sellOrders_.begin()->first;
}

int OrderBook::getVolumeAtPrice(double price) const {
    int volume = 0;
    
    auto buyIt = buyVolumes_.find(price);
    if (buyIt != buyVolumes_.end()) {
        volume += buyIt->second;
    }
    
    auto sellIt = sellVolumes_.find(price);
    if (sellIt != sellVolumes_.end()) {
        volume += sellIt->second;
    }
    
    return volume;
}

std::vector<std::pair<double, int>> OrderBook::getOrderBookSnapshot() const {
    std::vector<std::pair<double, int>> snapshot;
    
    // Add buy orders (in descending price order)
    for (const auto& [price, volume] : buyVolumes_) {
        snapshot.emplace_back(price, volume);
    }
    
    // Add sell orders (in ascending price order)
    for (const auto& [price, volume] : sellVolumes_) {
        snapshot.emplace_back(price, volume);
    }
    
    return snapshot;
}

} // namespace OrderBook 