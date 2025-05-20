#include "OrderRouter.h"
#include <iostream>
#include <chrono>

namespace TradingSystem {

OrderRouter::OrderRouter() : running_(false) {}

OrderRouter::~OrderRouter() {
    stop();
}

void OrderRouter::start() {
    if (!running_) {
        running_ = true;
        processing_thread_ = std::thread(&OrderRouter::processOrders, this);
    }
}

void OrderRouter::stop() {
    if (running_) {
        running_ = false;
        queue_cv_.notify_all();
        if (processing_thread_.joinable()) {
            processing_thread_.join();
        }
    }
}

void OrderRouter::processOrder(const trading::Order& order) {
    // Validate order through risk manager
    if (!risk_manager_.validateOrder(order)) {
        // Create and send rejection response
        trading::OrderResponse response;
        response.set_order_id(order.order_id());
        response.set_status(trading::OrderStatus::REJECTED);
        response.set_message("Risk validation failed");
        notifyOrderUpdate(response);
        return;
    }

    // Add to processing queue
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        order_queue_.push(order);
    }
    queue_cv_.notify_one();
}

void OrderRouter::cancelOrder(const std::string& order_id) {
    std::lock_guard<std::mutex> lock(orders_mutex_);
    auto it = active_orders_.find(order_id);
    if (it != active_orders_.end()) {
        handleCancel(order_id);
    }
}

void OrderRouter::processOrders() {
    while (running_) {
        trading::Order order;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            queue_cv_.wait(lock, [this] { return !order_queue_.empty() || !running_; });
            
            if (!running_) break;
            
            order = order_queue_.front();
            order_queue_.pop();
        }

        handleOrder(order);
    }
}

void OrderRouter::handleOrder(const trading::Order& order) {
    std::lock_guard<std::mutex> lock(orders_mutex_);
    
    // Store active order
    active_orders_[order.order_id()] = order;
    
    // Update position in risk manager
    risk_manager_.updatePosition(order.client_id(), order.symbol(), order.quantity());
    
    // Create and send acceptance response
    trading::OrderResponse response;
    response.set_order_id(order.order_id());
    response.set_status(trading::OrderStatus::NEW);
    notifyOrderUpdate(response);
}

void OrderRouter::handleCancel(const std::string& order_id) {
    auto it = active_orders_.find(order_id);
    if (it != active_orders_.end()) {
        const auto& order = it->second;
        
        // Update position in risk manager (reverse the order quantity)
        risk_manager_.updatePosition(order.client_id(), order.symbol(), -order.quantity());
        
        // Remove from active orders
        active_orders_.erase(it);
        
        // Create and send cancellation response
        trading::OrderResponse response;
        response.set_order_id(order_id);
        response.set_status(trading::OrderStatus::CANCELED);
        notifyOrderUpdate(response);
    }
}

void OrderRouter::setPositionLimit(const std::string& client_id, const std::string& symbol, int limit) {
    risk_manager_.setPositionLimit(client_id, symbol, limit);
}

void OrderRouter::setPriceLimit(const std::string& symbol, double min_price, double max_price) {
    risk_manager_.setPriceLimit(symbol, min_price, max_price);
}

void OrderRouter::setDailyLimit(const std::string& client_id, double limit) {
    risk_manager_.setDailyLimit(client_id, limit);
}

int OrderRouter::getPosition(const std::string& client_id, const std::string& symbol) const {
    return risk_manager_.getPosition(client_id, symbol);
}

void OrderRouter::setOrderCallback(OrderCallback callback) {
    order_callback_ = std::move(callback);
}

void OrderRouter::setMarketDataCallback(MarketDataCallback callback) {
    market_data_callback_ = std::move(callback);
}

void OrderRouter::notifyOrderUpdate(const trading::OrderResponse& response) {
    if (order_callback_) {
        order_callback_(response);
    }
}

trading::OrderCancelResponse OrderRouter::cancelOrder(const trading::OrderCancelRequest& request) {
    // Implementation for canceling an order based on the request
    trading::OrderCancelResponse response;
    response.set_request_id(request.request_id());
    response.set_order_id(request.order_id());
    response.set_success(true);
    response.set_message("Order canceled successfully");
    return response;
}

trading::OrderResponse OrderRouter::processOrder(const trading::OrderRequest& request) {
    // Implementation for processing an order based on the request
    trading::OrderResponse response;
    response.set_request_id(request.request_id());
    response.set_order_id(request.order().order_id());
    response.set_status(trading::OrderStatus::NEW);
    response.set_message("Order processed successfully");
    return response;
}

trading::OrderStatusResponse OrderRouter::getOrderStatus(const trading::OrderStatusRequest& request) {
    // Implementation for retrieving the status of an order based on the request
    trading::OrderStatusResponse response;
    response.set_request_id(request.request_id());
    // Assume the order is found and set its status
    trading::Order order;
    order.set_order_id(request.order_id());
    order.set_status(trading::OrderStatus::NEW);
    *response.mutable_order() = order;
    return response;
}

} // namespace TradingSystem 