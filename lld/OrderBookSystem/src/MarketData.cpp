#include "MarketData.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace OrderBook {

void MarketData::recordTrade(const Trade& trade) {
    trades_.push_back(trade);
    lastUpdate_ = std::chrono::system_clock::now();
}

std::vector<Trade> MarketData::getRecentTrades(size_t count) const {
    if (trades_.empty()) {
        return {};
    }
    
    size_t startIdx = (trades_.size() > count) ? trades_.size() - count : 0;
    return std::vector<Trade>(trades_.begin() + startIdx, trades_.end());
}

double MarketData::getLastTradePrice() const {
    if (trades_.empty()) {
        throw std::runtime_error("No trades recorded");
    }
    return trades_.back().price;
}

int MarketData::getVolumeInLastMinute() const {
    if (trades_.empty()) {
        return 0;
    }
    
    auto oneMinuteAgo = std::chrono::system_clock::now() - std::chrono::minutes(1);
    
    return std::accumulate(trades_.rbegin(), trades_.rend(), 0,
        [oneMinuteAgo](int sum, const Trade& trade) {
            if (trade.timestamp >= oneMinuteAgo) {
                return sum + trade.quantity;
            }
            return sum;
        });
}

double MarketData::getVWAP(size_t count) const {
    if (trades_.empty()) {
        throw std::runtime_error("No trades recorded");
    }
    
    size_t startIdx = (trades_.size() > count) ? trades_.size() - count : 0;
    auto begin = trades_.begin() + startIdx;
    auto end = trades_.end();
    
    double totalValue = 0.0;
    int totalVolume = 0;
    
    for (auto it = begin; it != end; ++it) {
        totalValue += it->price * it->quantity;
        totalVolume += it->quantity;
    }
    
    if (totalVolume == 0) {
        throw std::runtime_error("No volume in the specified period");
    }
    
    return totalValue / totalVolume;
}

} // namespace OrderBook 