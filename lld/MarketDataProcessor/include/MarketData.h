#pragma once

#include <string>
#include <chrono>
#include <atomic>

namespace MarketData {

struct MarketData {
    std::string symbol;
    double price;
    int quantity;
    std::chrono::system_clock::time_point timestamp;
    
    MarketData(const std::string& sym, double p, int q)
        : symbol(sym), price(p), quantity(q), 
          timestamp(std::chrono::system_clock::now()) {}
};

class MarketDataStats {
public:
    MarketDataStats() = default;
    
    void update(const MarketData& data) {
        totalVolume_ += data.quantity;
        lastPrice_ = data.price;
        lastUpdate_ = data.timestamp;
    }
    
    double getLastPrice() const { return lastPrice_; }
    int getTotalVolume() const { return totalVolume_; }
    std::chrono::system_clock::time_point getLastUpdate() const { return lastUpdate_; }
    
private:
    std::atomic<double> lastPrice_{0.0};
    std::atomic<int> totalVolume_{0};
    std::chrono::system_clock::time_point lastUpdate_;
};

} // namespace MarketData 