#pragma once

#include <unordered_map>
#include <mutex>
#include <memory>
#include <functional>
#include <string>
#include <queue>
#include <thread>
#include <atomic>
#include "TradingTypes.h"

namespace TradingSystem {

class OrderRouter {
public:
    OrderRouter();
    ~OrderRouter();

    // Prevent copying
    OrderRouter(const OrderRouter&) = delete;
    OrderRouter& operator=(const OrderRouter&) = delete;

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
    // Order storage
    struct OrderInfo {
        Order order;
        std::chrono::system_clock::time_point timestamp;
        std::string client_id;
    };

    std::unordered_map<std::string, OrderInfo> orders_;
    std::mutex orders_mutex_;

    // Callbacks
    OrderCallback order_callback_;
    MarketDataCallback market_data_callback_;

    // Processing thread
    std::thread processing_thread_;
    std::atomic<bool> running_{false};
    std::queue<OrderRequest> order_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_condition_;

    // Internal methods
    void processOrderQueue();
    void validateOrder(const Order& order, OrderResponse& response);
    void matchOrder(const Order& order, OrderResponse& response);
    void updateOrderStatus(const std::string& order_id, OrderStatus status);
    void notifyOrderUpdate(const OrderResponse& response);
    void notifyMarketData(const MarketDataResponse& response);
};

} // namespace TradingSystem 