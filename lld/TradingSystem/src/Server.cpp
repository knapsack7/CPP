#include "Server.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace TradingSystem {

Server::Server(const std::string& address, uint16_t port)
    : address_(address)
    , port_(port)
    , acceptor_(io_context_)
    , order_router_(std::make_unique<OrderRouter>())
    , market_data_stream_(std::make_unique<MarketDataStream>()) {
}

Server::~Server() {
    stop();
}

void Server::start() {
    if (running_) {
        return;
    }

    try {
        // Create endpoint
        boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::make_address(address_), port_);

        // Open acceptor
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        // Start accepting connections
        running_ = true;
        server_thread_ = std::thread(&Server::run, this);
        acceptConnections();

        std::cout << "Server started on " << address_ << ":" << port_ << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to start server: " << e.what() << std::endl;
        throw;
    }
}

void Server::stop() {
    if (!running_) {
        return;
    }

    running_ = false;
    acceptor_.close();
    io_context_.stop();

    if (server_thread_.joinable()) {
        server_thread_.join();
    }

    // Close all connections
    std::lock_guard<std::mutex> lock(connections_mutex_);
    connections_.clear();

    std::cout << "Server stopped" << std::endl;
}

void Server::acceptConnections() {
    acceptor_.async_accept(
        [this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
            if (!error) {
                handleNewConnection(std::move(socket));
            } else {
                std::cerr << "Accept error: " << error.message() << std::endl;
            }
            if (running_) {
                acceptConnections();
            }
        });
}

void Server::handleNewConnection(boost::asio::ip::tcp::socket socket) {
    auto connection = std::make_shared<Connection>(std::move(socket));
    
    connection->setMessageCallback([this](const std::vector<uint8_t>& message) {
        // Handle incoming messages
        // This will be implemented when we add message handling
    });

    connection->start();

    // Generate a unique client ID
    std::string clientId = "client_" + std::to_string(
        std::chrono::system_clock::now().time_since_epoch().count());

    connection->setClientId(clientId);

    std::lock_guard<std::mutex> lock(connections_mutex_);
    connections_[clientId] = connection;

    // Send connection status update
    ConnectionStatusUpdate status;
    status.set_status(ConnectionStatus::CONNECTED);
    status.set_client_id(clientId);
    status.set_timestamp(std::chrono::system_clock::now().time_since_epoch().count());
    status.set_message("Connected to server");

    connection->sendMessage(status);
}

void Server::removeConnection(const std::string& clientId) {
    std::lock_guard<std::mutex> lock(connections_mutex_);
    connections_.erase(clientId);
    handleClientDisconnection(clientId);
}

void Server::handleOrderRequest(const OrderRequest& request, const std::string& clientId) {
    OrderResponse response = order_router_->processOrder(request);
    
    std::lock_guard<std::mutex> lock(connections_mutex_);
    if (auto it = connections_.find(clientId); it != connections_.end()) {
        it->second->sendMessage(response);
    }
}

void Server::handleOrderCancelRequest(const OrderCancelRequest& request, const std::string& clientId) {
    OrderCancelResponse response = order_router_->cancelOrder(request);
    
    std::lock_guard<std::mutex> lock(connections_mutex_);
    if (auto it = connections_.find(clientId); it != connections_.end()) {
        it->second->sendMessage(response);
    }
}

void Server::handleOrderStatusRequest(const OrderStatusRequest& request, const std::string& clientId) {
    OrderStatusResponse response = order_router_->getOrderStatus(request);
    
    std::lock_guard<std::mutex> lock(connections_mutex_);
    if (auto it = connections_.find(clientId); it != connections_.end()) {
        it->second->sendMessage(response);
    }
}

void Server::handleMarketDataRequest(const MarketDataRequest& request, const std::string& clientId) {
    if (request.subscribe()) {
        market_data_stream_->subscribe(request.symbol(), [this](const trading::MarketDataResponse& resp, const std::string& symbol) {
            // Handle market data update
        });
    } else {
        market_data_stream_->unsubscribe(request.symbol());
    }
}

void Server::broadcastMarketData(const MarketDataResponse& response) {
    std::lock_guard<std::mutex> lock(connections_mutex_);
    for (const auto& [clientId, connection] : connections_) {
        connection->sendMessage(response);
    }
}

bool Server::authenticateClient(const LoginRequest& request, LoginResponse& response) {
    // TODO: Implement proper authentication
    response.set_success(true);
    response.set_session_id("session_" + std::to_string(
        std::chrono::system_clock::now().time_since_epoch().count()));
    response.set_message("Login successful");
    response.set_timestamp(std::chrono::system_clock::now().time_since_epoch().count());
    return true;
}

void Server::handleLogout(const LogoutRequest& request, LogoutResponse& response) {
    response.set_success(true);
    response.set_message("Logout successful");
    response.set_timestamp(std::chrono::system_clock::now().time_since_epoch().count());
    
    removeConnection(request.client_id());
}

void Server::run() {
    try {
        io_context_.run();
    } catch (const std::exception& e) {
        std::cerr << "IO context error: " << e.what() << std::endl;
    }
}

void Server::handleClientDisconnection(const std::string& clientId) {
    // Unsubscribe from market data
    // market_data_stream_->unsubscribeAll(clientId); // Remove or replace with appropriate method

    // Send system message about disconnection
    SystemMessage message;
    message.set_type(MessageType::INFO);
    message.set_message("Client disconnected");
    message.set_code(0);
    message.set_timestamp(std::chrono::system_clock::now().time_since_epoch().count());

    broadcastSystemMessage(message);
}

void Server::broadcastSystemMessage(const SystemMessage& message) {
    std::lock_guard<std::mutex> lock(connections_mutex_);
    for (const auto& [clientId, connection] : connections_) {
        connection->sendMessage(message);
    }
}

} // namespace TradingSystem 