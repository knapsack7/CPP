#include "Server.h"
#include "Client.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace TradingSystem;

void printOrderResponse(const OrderResponse& response) {
    std::cout << "Order Response:" << std::endl
              << "  Order ID: " << response.order_id() << std::endl
              << "  Message: " << response.message() << std::endl
              << "  Status: " << OrderStatus_Name(response.status()) << std::endl;
}

void printMarketData(const MarketDataResponse& response) {
    std::cout << "Market Data:" << std::endl;
    if (response.has_trade()) {
        std::cout << "  Symbol: " << response.trade().symbol() << std::endl;
    } else if (response.has_quote()) {
        std::cout << "  Symbol: " << response.quote().symbol() << std::endl;
    }
    std::cout << "  Type: " << MarketDataType_Name(response.type()) << std::endl;
}

void printSystemMessage(const SystemMessage& message) {
    std::cout << "System Message:" << std::endl
              << "  Type: " << MessageType_Name(message.type()) << std::endl
              << "  Message: " << message.message() << std::endl
              << "  Code: " << message.code() << std::endl;
}

int main() {
    try {
        // Start server
        Server server("127.0.0.1", 8080);
        server.start();

        // Create client
        Client client("127.0.0.1", "8080");
        
        // Set callbacks
        // client.setOrderCallback(printOrderResponse);
        // client.setMarketDataCallback(printMarketData);
        // client.setSystemMessageCallback(printSystemMessage);

        // Login
        if (!client.login("test_user", "test_password")) {
            std::cerr << "Failed to login" << std::endl;
            return 1;
        }

        // Subscribe to market data
        client.subscribeMarketData("AAPL", MarketDataType::TRADE);
        client.subscribeMarketData("AAPL", MarketDataType::QUOTE);

        // Place an order (use correct signature)
        if (!client.placeOrder("AAPL", 150.50, 100, OrderSide::BUY)) {
            std::cerr << "Failed to place order" << std::endl;
            return 1;
        }

        // Wait for a while to receive responses
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Cancel the order
        if (!client.cancelOrder("order_1")) {
            std::cerr << "Failed to cancel order" << std::endl;
            return 1;
        }

        // Wait for a while to receive responses
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Logout
        client.logout();

        // Stop server
        server.stop();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 