#pragma once

#include "Order.h"
#include <vector>
#include <memory>
#include <chrono>

namespace OrderBook {

struct Trade {
    std::string buyOrderId;
    std::string sellOrderId;
    double price;
    int quantity;
    std::chrono::system_clock::time_point timestamp;
};

class MarketData {
public:
    MarketData() = default;
    ~MarketData() = default;

    // Prevent copying
    MarketData(const MarketData&) = delete;
    MarketData& operator=(const MarketData&) = delete;

    // Allow moving
    MarketData(MarketData&&) = default;
    MarketData& operator=(MarketData&&) = default;

    // Trade recording
    void recordTrade(const Trade& trade);
    
    // Market data queries
    std::vector<Trade> getRecentTrades(size_t count) const;
    double getLastTradePrice() const;
    int getVolumeInLastMinute() const;
    double getVWAP(size_t count) const;  // Volume Weighted Average Price

private:
    std::vector<Trade> trades_;
    std::chrono::system_clock::time_point lastUpdate_;
};

} // namespace OrderBook 