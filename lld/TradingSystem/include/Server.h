#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <functional>
#include "Connection.h"
#include "OrderRouter.h"
#include "MarketDataStream.h"
#include "TradingTypes.h"

namespace TradingSystem {

class Server {
public:
    Server(const std::string& address, uint16_t port);
    ~Server();

    // Prevent copying
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    // Core server operations
    void start();
    void stop();

    // Message handlers
    void handleOrderRequest(const OrderRequest& request, const std::string& clientId);
    void handleOrderCancelRequest(const OrderCancelRequest& request, const std::string& clientId);
    void handleOrderStatusRequest(const OrderStatusRequest& request, const std::string& clientId);
    void handleMarketDataRequest(const MarketDataRequest& request, const std::string& clientId);
    void broadcastMarketData(const MarketDataResponse& response);

    // Authentication
    bool authenticateClient(const LoginRequest& request, LoginResponse& response);
    void handleLogout(const LogoutRequest& request, LogoutResponse& response);

private:
    // Server configuration
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::string address_;
    uint16_t port_;
    std::atomic<bool> running_{false};
    std::thread server_thread_;

    // Core components
    std::unique_ptr<OrderRouter> order_router_;
    std::unique_ptr<MarketDataStream> market_data_stream_;
    std::unordered_map<std::string, std::shared_ptr<Connection>> connections_;
    std::mutex connections_mutex_;

    // Internal methods
    void acceptConnections();
    void run();
    void handleNewConnection(boost::asio::ip::tcp::socket socket);
    void removeConnection(const std::string& clientId);
    void handleClientDisconnection(const std::string& clientId);
    void broadcastSystemMessage(const SystemMessage& message);
};

} // namespace TradingSystem 