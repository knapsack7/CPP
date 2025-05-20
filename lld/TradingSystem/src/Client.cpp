#include "Client.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>
#include <iomanip>

namespace TradingSystem {

Client::Client(const std::string& host, const std::string& port)
    : io_context_()
    , socket_(io_context_)
    , host_(host)
    , port_(port)
    , client_id_()
    , active_(false)
{
}

Client::Client(const std::string& host, uint16_t port)
    : Client(host, std::to_string(port)) {}

Client::~Client() {
    stop();
}

void Client::start() {
    if (active_) return;
    
    boost::asio::ip::tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(host_, port_);
    
    boost::asio::connect(socket_, endpoints);
    active_ = true;
    
    // Start reading messages
    startReading();
}

void Client::stop() {
    if (!active_) return;
    
    active_ = false;
    socket_.close();
}

void Client::startReading() {
    if (!active_) return;
    
    socket_.async_read_some(
        boost::asio::buffer(read_buffer_),
        [this](const boost::system::error_code& error, size_t bytes_transferred) {
            if (!error) {
                handleRead(error, bytes_transferred);
            } else {
                stop();
            }
        }
    );
}

void Client::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        // Process received data
        std::vector<uint8_t> message(read_buffer_.data(), read_buffer_.data() + bytes_transferred);
        processMessage(message);
        
        // Continue reading
        startReading();
    } else {
        stop();
    }
}

void Client::processMessage(const std::vector<uint8_t>& message) {
    if (message.empty()) return;
    
    uint8_t message_type = message[0];
    std::vector<uint8_t> payload(message.begin() + 1, message.end());
    
    switch (message_type) {
        case static_cast<uint8_t>(trading::MessageType::INFO): {
            trading::SystemMessage system_msg;
            if (system_msg.ParseFromArray(payload.data(), payload.size())) {
                // Handle system message
            }
            break;
        }
        case static_cast<uint8_t>(trading::MessageType::WARNING): {
            trading::SystemMessage system_msg;
            if (system_msg.ParseFromArray(payload.data(), payload.size())) {
                // Handle warning message
            }
            break;
        }
        case static_cast<uint8_t>(trading::MessageType::ERROR): {
            trading::SystemMessage system_msg;
            if (system_msg.ParseFromArray(payload.data(), payload.size())) {
                // Handle error message
            }
            break;
        }
        case static_cast<uint8_t>(trading::MessageType::DEBUG): {
            trading::SystemMessage system_msg;
            if (system_msg.ParseFromArray(payload.data(), payload.size())) {
                // Handle debug message
            }
            break;
        }
    }
}

bool Client::login(const std::string& username, const std::string& password) {
    if (!active_) return false;
    
    trading::LoginRequest request;
    request.set_username(username);
    request.set_password(password);
    request.set_client_id(client_id_);
    
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    
    send(message);
    return true;
}

bool Client::logout() {
    if (!active_) return false;
    
    trading::LogoutRequest request;
    request.set_session_id(client_id_);
    request.set_client_id(client_id_);
    
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    
    send(message);
    return true;
}

bool Client::placeOrder(const std::string& symbol, double price, int quantity, trading::OrderSide side) {
    if (!active_) return false;
    
    trading::OrderRequest request;
    trading::Order* order = request.mutable_order();
    order->set_symbol(symbol);
    order->set_price(price);
    order->set_quantity(quantity);
    order->set_side(side);
    order->set_type(trading::OrderType::LIMIT);
    order->set_status(trading::OrderStatus::NEW);
    order->set_client_id(client_id_);
    
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    
    send(message);
    return true;
}

bool Client::cancelOrder(const std::string& order_id) {
    if (!active_) return false;
    
    trading::OrderCancelRequest request;
    request.set_order_id(order_id);
    request.set_client_id(client_id_);
    
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    
    send(message);
    return true;
}

void Client::send(const std::vector<uint8_t>& data) {
    if (!active_) return;
    
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(data),
        [this](const boost::system::error_code& error, size_t bytes_transferred) {
            if (error) {
                stop();
            }
        }
    );
}

bool Client::getOrderStatus(const std::string& orderId) {
    if (!active_) {
        return false;
    }
    trading::OrderStatusRequest request;
    request.set_request_id(generateRequestId());
    request.set_order_id(orderId);
    request.set_client_id(client_id_);
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    send(message);
    return true;
}

bool Client::subscribeMarketData(const std::string& symbol, trading::MarketDataType type) {
    if (!active_) {
        return false;
    }
    trading::MarketDataRequest request;
    request.set_request_id(generateRequestId());
    request.set_symbol(symbol);
    request.set_type(type);
    request.set_subscribe(true);
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    send(message);
    return true;
}

bool Client::unsubscribeMarketData(const std::string& symbol, trading::MarketDataType type) {
    if (!active_) {
        return false;
    }
    trading::MarketDataRequest request;
    request.set_request_id(generateRequestId());
    request.set_symbol(symbol);
    request.set_type(type);
    request.set_subscribe(false);
    std::vector<uint8_t> message;
    message.push_back(static_cast<uint8_t>(trading::MessageType::INFO));
    std::string serialized;
    request.SerializeToString(&serialized);
    message.insert(message.end(), serialized.begin(), serialized.end());
    send(message);
    return true;
}

std::string Client::generateRequestId() {
    static std::atomic<uint64_t> counter{0};
    return "req_" + std::to_string(++counter);
}

std::string Client::generateOrderId() {
    static std::atomic<uint64_t> counter{0};
    return "order_" + std::to_string(++counter);
}

} // namespace TradingSystem 