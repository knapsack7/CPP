#pragma once

#include <unordered_map>
#include <mutex>
#include <string>
#include <memory>
#include "Protocol.h"

namespace TradingSystem {

class RiskManager {
public:
    RiskManager();
    ~RiskManager() = default;

    // Prevent copying
    RiskManager(const RiskManager&) = delete;
    RiskManager& operator=(const RiskManager&) = delete;

    // Risk checks for orders
    bool validateOrder(const trading::Order& order);
    bool checkPositionLimit(const std::string& client_id, const std::string& symbol, int quantity);
    bool checkPriceLimit(const std::string& symbol, double price);
    bool checkDailyLimit(const std::string& client_id, double amount);

    // Risk limits management
    void setPositionLimit(const std::string& client_id, const std::string& symbol, int limit);
    void setPriceLimit(const std::string& symbol, double min_price, double max_price);
    void setDailyLimit(const std::string& client_id, double limit);

    // Position tracking
    void updatePosition(const std::string& client_id, const std::string& symbol, int quantity);
    int getPosition(const std::string& client_id, const std::string& symbol) const;

    void updateDailyTotal(const std::string& client_id, double amount);

private:
    struct PositionLimit {
        int limit;
        int current;
    };

    struct PriceLimit {
        double min_price;
        double max_price;
    };

    struct DailyLimit {
        double limit;
        double current;
    };

    // Risk limits storage
    std::unordered_map<std::string, std::unordered_map<std::string, PositionLimit>> position_limits_;
    std::unordered_map<std::string, PriceLimit> price_limits_;
    std::unordered_map<std::string, DailyLimit> daily_limits_;

    // Mutex for thread safety
    mutable std::mutex mutex_;
};

} // namespace TradingSystem 