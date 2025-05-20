#pragma once

#include <boost/asio.hpp>
#include <vector>
#include <queue>
#include <mutex>
#include <atomic>
#include <functional>
#include <string>
#include "Protocol.h"

namespace TradingSystem {

class Connection {
public:
    using MessageCallback = std::function<void(const std::vector<uint8_t>&)>;

    Connection(boost::asio::ip::tcp::socket socket);
    ~Connection();

    // Prevent copying
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    // Core functionality
    void start();
    void stop();
    bool isActive() const { return active_; }
    void setClientId(const std::string& id) { client_id_ = id; }
    const std::string& getClientId() const { return client_id_; }
    void setMessageCallback(MessageCallback callback) { message_callback_ = std::move(callback); }

    // Message handling
    template<typename Message>
    void sendMessage(const Message& message) {
        std::vector<uint8_t> buffer;
        Protocol::serialize(message, buffer);
        send(buffer);
    }

    void processMessage(const std::vector<uint8_t>& message);

private:
    // Core components
    boost::asio::ip::tcp::socket socket_;
    std::atomic<bool> active_{false};
    std::string client_id_;
    MessageCallback message_callback_;

    // Buffer management
    std::vector<uint8_t> read_buffer_;
    std::queue<std::vector<uint8_t>> write_queue_;
    std::mutex write_queue_mutex_;

    // Internal methods
    void startReading();
    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);
    void send(const std::vector<uint8_t>& data);
};

} // namespace TradingSystem 