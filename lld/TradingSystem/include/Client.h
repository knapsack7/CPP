#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <atomic>
#include <functional>
#include "system.pb.h"
#include "order.pb.h"
#include "market_data.pb.h"

namespace TradingSystem {

class Client {
public:
    // Callback types
    using OrderCallback = std::function<void(const trading::OrderResponse&)>;
    using MarketDataCallback = std::function<void(const trading::MarketDataResponse&)>;
    using SystemMessageCallback = std::function<void(const trading::SystemMessage&)>;

    Client(const std::string& host, const std::string& port);
    Client(const std::string& host, uint16_t port);
    ~Client();

    // Prevent copying
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    // Core operations
    void start();
    void stop();
    bool login(const std::string& username, const std::string& password);
    bool logout();

    // Trading operations
    bool placeOrder(const std::string& symbol, double price, int quantity, trading::OrderSide side);
    bool cancelOrder(const std::string& order_id);
    bool getOrderStatus(const std::string& order_id);

    // Market data operations
    bool subscribeMarketData(const std::string& symbol, trading::MarketDataType type);
    bool unsubscribeMarketData(const std::string& symbol, trading::MarketDataType type);

    // Callback registration
    void setOrderCallback(OrderCallback callback) { order_callback_ = std::move(callback); }
    void setMarketDataCallback(MarketDataCallback callback) { market_data_callback_ = std::move(callback); }
    void setSystemMessageCallback(SystemMessageCallback callback) { system_message_callback_ = std::move(callback); }

private:
    // Core components
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string host_;
    std::string port_;
    std::string client_id_;
    std::atomic<bool> active_{false};
    std::vector<uint8_t> read_buffer_;

    // Callbacks
    OrderCallback order_callback_;
    MarketDataCallback market_data_callback_;
    SystemMessageCallback system_message_callback_;

    // Internal methods
    void startReading();
    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
    void processMessage(const std::vector<uint8_t>& message);
    void send(const std::vector<uint8_t>& data);
    std::string generateRequestId();
    std::string generateOrderId();
};

} // namespace TradingSystem 