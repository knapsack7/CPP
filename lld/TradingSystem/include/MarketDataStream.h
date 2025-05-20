#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include "market_data.pb.h"

namespace TradingSystem {

using MarketDataCallback = std::function<void(const trading::MarketDataResponse&, const std::string&)>;

class MarketDataStream {
public:
    MarketDataStream();
    ~MarketDataStream();

    // Prevent copying
    MarketDataStream(const MarketDataStream&) = delete;
    MarketDataStream& operator=(const MarketDataStream&) = delete;

    // Lifecycle management
    void start();
    void stop();

    // Market data publishing
    void publishTrade(const trading::Trade& trade);
    void publishQuote(const trading::Quote& quote);
    void publishDepth(const trading::Depth& depth);
    void publishSummary(const trading::MarketSummary& summary);

    // Subscription management
    void subscribe(const std::string& symbol, MarketDataCallback callback);
    void unsubscribe(const std::string& symbol);

private:
    // State
    bool active_;

    // Subscription storage
    std::unordered_map<std::string, MarketDataCallback> subscribers_;

    // Internal methods
    void notifySubscribers(const trading::MarketDataResponse& response, const std::string& symbol);
};

} // namespace TradingSystem 