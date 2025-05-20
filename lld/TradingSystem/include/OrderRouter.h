#pragma once

#include <unordered_map>
#include <mutex>
#include <memory>
#include <functional>
#include <string>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "TradingTypes.h"
#include "Protocol.h"
#include "RiskManager.h"

namespace TradingSystem {

class OrderRouter {
public:
    OrderRouter();
    ~OrderRouter();

    // Prevent copying
    OrderRouter(const OrderRouter&) = delete;
    OrderRouter& operator=(const OrderRouter&) = delete;

    // Core operations
    void start();
    void stop();
    void processOrder(const trading::Order& order);
    void cancelOrder(const std::string& order_id);

    // Risk management
    void setPositionLimit(const std::string& client_id, const std::string& symbol, int limit);
    void setPriceLimit(const std::string& symbol, double min_price, double max_price);
    void setDailyLimit(const std::string& client_id, double limit);
    int getPosition(const std::string& client_id, const std::string& symbol) const;

    // Order management
    OrderResponse processOrder(const OrderRequest& request);
    OrderCancelResponse cancelOrder(const OrderCancelRequest& request);
    OrderStatusResponse getOrderStatus(const OrderStatusRequest& request);

    // Order callback registration
    using OrderCallback = std::function<void(const OrderResponse&)>;
    void setOrderCallback(OrderCallback callback);

    // Market data callback registration
    using MarketDataCallback = std::function<void(const MarketDataResponse&)>;
    void setMarketDataCallback(MarketDataCallback callback);

private:
    // Order processing
    void processOrders();
    void handleOrder(const trading::Order& order);
    void handleCancel(const std::string& order_id);
    void updateOrderStatus(const std::string& order_id, trading::OrderStatus status);
    void notifyOrderUpdate(const trading::OrderResponse& response);

    // Core components
    std::queue<trading::Order> order_queue_;
    std::unordered_map<std::string, trading::Order> active_orders_;
    std::mutex queue_mutex_;
    std::mutex orders_mutex_;
    std::condition_variable queue_cv_;
    std::thread processing_thread_;
    std::atomic<bool> running_;
    RiskManager risk_manager_;

    // Callbacks
    OrderCallback order_callback_;
    MarketDataCallback market_data_callback_;
};

} // namespace TradingSystem 