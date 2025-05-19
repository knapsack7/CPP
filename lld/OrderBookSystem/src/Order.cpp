#include "Order.h"
#include <sstream>
#include <iomanip>
#include <random>

namespace OrderBook {

Order::Order(double price, int quantity, OrderType type)
    : price_(price)
    , quantity_(quantity)
    , type_(type)
    , orderId_(generateOrderId())
    , timestamp_(std::chrono::system_clock::now())
{
}

std::string Order::generateOrderId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static const char* hex = "0123456789abcdef";
    
    std::string uuid;
    uuid.reserve(36);
    
    for (int i = 0; i < 36; ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid += '-';
        } else {
            uuid += hex[dis(gen)];
        }
    }
    
    return uuid;
}

} // namespace OrderBook 