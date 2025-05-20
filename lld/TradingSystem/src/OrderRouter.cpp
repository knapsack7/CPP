#include "OrderRouter.h"
#include <iostream>
#include <chrono>

namespace TradingSystem {

OrderRouter::OrderRouter() {
    // startProcessing();
}

OrderRouter::~OrderRouter() {
    running_ = false;
    queue_condition_.notify_all();
    if (processing_thread_.joinable()) {
        processing_thread_.join();
    }
}

OrderResponse OrderRouter::processOrder(const OrderRequest& request) {
    OrderResponse response;
    response.set_request_id(request.request_id());
    response.set_order_id(request.order().order_id());
    response.set_status(OrderStatus::NEW); // Default status
    // response.set_client_id(request.client_id()); // Not in proto
    // response.set_timestamp(...) // Not in proto
    // response.set_success(...) // Not in proto
    // response.set_message(...) // Not in proto

    try {
        // Validate order
        validateOrder(request.order(), response);

        // Add to processing queue
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            order_queue_.push(request);
        }
        queue_condition_.notify_one();

        // response.set_success(true); // Not in proto
        // response.set_message("Order accepted for processing"); // Not in proto
    } catch (const std::exception& e) {
        // response.set_success(false); // Not in proto
        // response.set_message(std::string("Error processing order: ") + e.what()); // Not in proto
    }

    return response;
}

OrderCancelResponse OrderRouter::cancelOrder(const OrderCancelRequest& request) {
    OrderCancelResponse response;
    response.set_request_id(request.request_id());
    response.set_order_id(request.order_id());
    // response.set_client_id(request.client_id()); // Not in proto
    // response.set_timestamp(...) // Not in proto
    // response.set_success(...) // Not in proto
    // response.set_message(...) // Not in proto

    try {
        std::lock_guard<std::mutex> lock(orders_mutex_);
        auto it = orders_.find(request.order_id());
        
        if (it == orders_.end()) {
            // response.set_success(false); // Not in proto
            // response.set_message("Order not found"); // Not in proto
            return response;
        }

        if (it->second.client_id != request.client_id()) {
            // response.set_success(false); // Not in proto
            // response.set_message("Unauthorized to cancel this order"); // Not in proto
            return response;
        }

        // Update order status
        updateOrderStatus(request.order_id(), OrderStatus::CANCELED);
        
        // response.set_success(true); // Not in proto
        // response.set_message("Order cancelled successfully"); // Not in proto
    } catch (const std::exception& e) {
        // response.set_success(false); // Not in proto
        // response.set_message(std::string("Error cancelling order: ") + e.what()); // Not in proto
    }

    return response;
}

OrderStatusResponse OrderRouter::getOrderStatus(const OrderStatusRequest& request) {
    OrderStatusResponse response;
    response.set_request_id(request.request_id());
    // response.set_order_id(request.order_id()); // Not in proto
    // response.set_client_id(request.client_id()); // Not in proto
    // response.set_timestamp(...) // Not in proto
    // response.set_success(...) // Not in proto
    // response.set_message(...) // Not in proto
    // response.set_status(...) // Not in proto

    try {
        std::lock_guard<std::mutex> lock(orders_mutex_);
        auto it = orders_.find(request.order_id());
        
        if (it == orders_.end()) {
            // response.set_success(false); // Not in proto
            // response.set_message("Order not found"); // Not in proto
            return response;
        }

        if (it->second.client_id != request.client_id()) {
            // response.set_success(false); // Not in proto
            // response.set_message("Unauthorized to view this order"); // Not in proto
            return response;
        }

        // response.set_success(true); // Not in proto
        // response.set_message("Order status retrieved successfully"); // Not in proto
    } catch (const std::exception& e) {
        // response.set_success(false); // Not in proto
        // response.set_message(std::string("Error getting order status: ") + e.what()); // Not in proto
    }

    return response;
}

void OrderRouter::setOrderCallback(OrderCallback callback) {
    order_callback_ = std::move(callback);
}

void OrderRouter::setMarketDataCallback(MarketDataCallback callback) {
    market_data_callback_ = std::move(callback);
}

void OrderRouter::processOrderQueue() {
    while (running_) {
        OrderRequest request;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            queue_condition_.wait(lock, [this] { 
                return !order_queue_.empty() || !running_; 
            });

            if (!running_) {
                break;
            }

            request = order_queue_.front();
            order_queue_.pop();
        }

        try {
            // Process the order
            OrderResponse response;
            response.set_request_id(request.request_id());
            response.set_order_id(request.order().order_id());
            response.set_status(OrderStatus::NEW); // Default status

            // Match the order
            matchOrder(request.order(), response);

            // Store the order
            {
                std::lock_guard<std::mutex> lock(orders_mutex_);
                OrderInfo info;
                info.order = request.order();
                info.timestamp = std::chrono::system_clock::now();
                info.client_id = ""; // Not in proto, set to empty or remove
                orders_[request.order().order_id()] = info;
            }

            // Notify about the order update
            notifyOrderUpdate(response);
        } catch (const std::exception& e) {
            std::cerr << "Error processing order: " << e.what() << std::endl;
        }
    }
}

void OrderRouter::validateOrder(const Order& order, OrderResponse& response) {
    // Basic validation
    if (order.symbol().empty()) {
        // response.set_success(false); // Not in proto
        // response.set_message("Invalid symbol"); // Not in proto
        return;
    }

    if (order.quantity() <= 0) {
        // response.set_success(false); // Not in proto
        // response.set_message("Invalid quantity"); // Not in proto
        return;
    }

    if (order.price() <= 0) {
        // response.set_success(false); // Not in proto
        // response.set_message("Invalid price"); // Not in proto
        return;
    }

    // Check for duplicate order ID
    std::lock_guard<std::mutex> lock(orders_mutex_);
    if (orders_.find(order.order_id()) != orders_.end()) {
        // response.set_success(false); // Not in proto
        // response.set_message("Duplicate order ID"); // Not in proto
        return;
    }

    // response.set_success(true); // Not in proto
}

void OrderRouter::matchOrder(const Order& order, OrderResponse& response) {
    // TODO: Implement order matching logic
    // For now, just mark the order as accepted
    response.set_message("Order accepted");
}

void OrderRouter::updateOrderStatus(const std::string& order_id, OrderStatus status) {
    std::lock_guard<std::mutex> lock(orders_mutex_);
    auto it = orders_.find(order_id);
    if (it != orders_.end()) {
        it->second.order.set_status(status);
    }
}

void OrderRouter::notifyOrderUpdate(const OrderResponse& response) {
    if (order_callback_) {
        order_callback_(response);
    }
}

void OrderRouter::notifyMarketData(const MarketDataResponse& response) {
    if (market_data_callback_) {
        market_data_callback_(response);
    }
}

} // namespace TradingSystem 