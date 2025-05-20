#include "MarketDataStream.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace TradingSystem {

MarketDataStream::MarketDataStream()
    : active_(false) {
}

MarketDataStream::~MarketDataStream() {
    stop();
}

void MarketDataStream::start() {
    // Stub implementation
}

void MarketDataStream::stop() {
    // Stub implementation
}

void MarketDataStream::subscribe(const std::string& symbol, std::function<void(const trading::MarketDataResponse&, const std::string&)> callback) {
    // Stub implementation
}

void MarketDataStream::unsubscribe(const std::string& symbol) {
    // Stub implementation
}

void MarketDataStream::publishTrade(const trading::Trade& trade) {
    if (!active_) return;
    
    trading::MarketDataResponse response;
    response.set_type(trading::MarketDataType::TRADE);
    *response.mutable_trade() = trade;
    
    notifySubscribers(response, trade.symbol());
}

void MarketDataStream::publishQuote(const trading::Quote& quote) {
    if (!active_) return;
    
    trading::MarketDataResponse response;
    response.set_type(trading::MarketDataType::QUOTE);
    *response.mutable_quote() = quote;
    
    notifySubscribers(response, quote.symbol());
}

void MarketDataStream::publishDepth(const trading::Depth& depth) {
    if (!active_) return;
    
    trading::MarketDataResponse response;
    response.set_type(trading::MarketDataType::DEPTH);
    *response.mutable_depth() = depth;
    
    notifySubscribers(response, depth.symbol());
}

void MarketDataStream::publishSummary(const trading::MarketSummary& summary) {
    if (!active_) return;
    
    trading::MarketDataResponse response;
    response.set_type(trading::MarketDataType::SUMMARY);
    *response.mutable_summary() = summary;
    
    notifySubscribers(response, summary.symbol());
}

void MarketDataStream::notifySubscribers(const trading::MarketDataResponse& response, const std::string& symbol) {
    auto it = subscribers_.find(symbol);
    if (it != subscribers_.end()) {
        it->second(response, symbol);
    }
}

} // namespace TradingSystem 