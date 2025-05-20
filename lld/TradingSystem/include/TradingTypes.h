#pragma once

// Include generated protocol buffer headers
#include "order.pb.h"
#include "market_data.pb.h"
#include "system.pb.h"

namespace TradingSystem {
    // Re-export types from the trading namespace
    using trading::Order;
    using trading::OrderRequest;
    using trading::OrderResponse;
    using trading::OrderCancelRequest;
    using trading::OrderCancelResponse;
    using trading::OrderStatusRequest;
    using trading::OrderStatusResponse;
    using trading::OrderType;
    using trading::OrderSide;
    using trading::OrderStatus;

    using trading::Trade;
    using trading::Quote;
    using trading::Depth;
    using trading::DepthLevel;
    using trading::MarketSummary;
    using trading::MarketDataRequest;
    using trading::MarketDataResponse;
    using trading::MarketDataType;

    using trading::SystemMessage;
    using trading::Heartbeat;
    using trading::ConnectionStatusUpdate;
    using trading::LoginRequest;
    using trading::LoginResponse;
    using trading::LogoutRequest;
    using trading::LogoutResponse;
    using trading::MessageType;
    using trading::ConnectionStatus;
} 