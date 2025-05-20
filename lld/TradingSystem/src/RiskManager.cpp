#include "RiskManager.h"
#include <stdexcept>
#include <iostream>

namespace TradingSystem {

RiskManager::RiskManager() = default;

bool RiskManager::validateOrder(const trading::Order& order) {
    // std::cout << "Validating order for client: " << order.client_id() << ", symbol: " << order.symbol() << ", quantity: " << order.quantity() << ", price: " << order.price() << std::endl;
    // Check if the order meets basic validation criteria
    if (order.symbol().empty() || order.price() <= 0 || order.quantity() <= 0) {
        // std::cout << "Order failed basic validation criteria." << std::endl;
        return false;
    }

    // Check position limits
    if (!checkPositionLimit(order.client_id(), order.symbol(), order.quantity())) {
        // std::cout << "Order failed position limit check." << std::endl;
        return false;
    }

    // Check price limits
    if (!checkPriceLimit(order.symbol(), order.price())) {
        // std::cout << "Order failed price limit check." << std::endl;
        return false;
    }

    // Check daily limits
    if (!checkDailyLimit(order.client_id(), order.price() * order.quantity())) {
        // std::cout << "Order failed daily limit check." << std::endl;
        return false;
    }

    // std::cout << "Order passed all validation checks." << std::endl;
    return true;
}

bool RiskManager::checkPositionLimit(const std::string& client_id, const std::string& symbol, int quantity) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto& client_positions = position_limits_[client_id];
    auto it = client_positions.find(symbol);
    
    if (it == client_positions.end()) {
        // std::cout << "No position limit set for client: " << client_id << ", symbol: " << symbol << std::endl;
        return true;
    }

    PositionLimit& limit = it->second;
    int new_position = limit.current + quantity;
    
    // std::cout << "Checking position limit for client: " << client_id << ", symbol: " << symbol << ", current: " << current_position << ", new: " << new_position << ", limit: " << limit << std::endl;
    return new_position <= limit.limit;
}

bool RiskManager::checkPriceLimit(const std::string& symbol, double price) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = price_limits_.find(symbol);
    if (it == price_limits_.end()) {
        // No price limits set for this symbol
        return true;
    }

    const PriceLimit& limit = it->second;
    return price >= limit.min_price && price <= limit.max_price;
}

bool RiskManager::checkDailyLimit(const std::string& client_id, double amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = daily_limits_.find(client_id);
    if (it == daily_limits_.end()) {
        // No daily limit set for this client
        return true;
    }

    DailyLimit& limit = it->second;
    double new_total = limit.current + amount;
    
    return new_total <= limit.limit;
}

void RiskManager::setPositionLimit(const std::string& client_id, const std::string& symbol, int limit) {
    std::lock_guard<std::mutex> lock(mutex_);
    position_limits_[client_id][symbol] = {limit, 0};
}

void RiskManager::setPriceLimit(const std::string& symbol, double min_price, double max_price) {
    std::lock_guard<std::mutex> lock(mutex_);
    price_limits_[symbol] = {min_price, max_price};
}

void RiskManager::setDailyLimit(const std::string& client_id, double limit) {
    std::lock_guard<std::mutex> lock(mutex_);
    daily_limits_[client_id] = {limit, 0.0};
}

void RiskManager::updatePosition(const std::string& client_id, const std::string& symbol, int quantity) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto& client_positions = position_limits_[client_id];
    client_positions[symbol].current += quantity;
}

int RiskManager::getPosition(const std::string& client_id, const std::string& symbol) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = position_limits_.find(client_id);
    if (it == position_limits_.end()) {
        return 0;
    }
    
    auto symbol_it = it->second.find(symbol);
    if (symbol_it == it->second.end()) {
        return 0;
    }
    
    return symbol_it->second.current;
}

void RiskManager::updateDailyTotal(const std::string& client_id, double amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = daily_limits_.find(client_id);
    if (it != daily_limits_.end()) {
        it->second.current += amount;
    }
}

} // namespace TradingSystem 