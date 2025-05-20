#pragma once

#include <vector>
#include <string>
#include <google/protobuf/message.h>
#include "TradingTypes.h"

namespace TradingSystem {

class Protocol {
public:
    // Message types
    enum class MessageType : uint8_t {
        ORDER = 1,
        ORDER_CANCEL = 2,
        ORDER_STATUS = 3,
        MARKET_DATA = 4,
        SYSTEM = 5,
        AUTH = 6
    };

    // Message header structure
    struct MessageHeader {
        uint32_t size;
        MessageType type;
    };

    // Serialization
    template<typename Message>
    static void serialize(const Message& message, std::vector<uint8_t>& buffer) {
        // Serialize message
        std::string serialized;
        message.SerializeToString(&serialized);

        // Create header
        MessageHeader header{
            static_cast<uint32_t>(serialized.size()),
            getMessageType(message)
        };

        // Prepare buffer
        buffer.resize(sizeof(header) + serialized.size());
        
        // Write header and message
        std::memcpy(buffer.data(), &header, sizeof(header));
        std::memcpy(buffer.data() + sizeof(header), serialized.data(), serialized.size());
    }

    // Deserialization
    template<typename Message>
    static bool deserialize(const std::vector<uint8_t>& buffer, Message& message) {
        if (buffer.size() < sizeof(MessageHeader)) {
            return false;
        }

        // Read header
        MessageHeader header;
        std::memcpy(&header, buffer.data(), sizeof(header));

        // Validate message size
        if (buffer.size() != sizeof(header) + header.size) {
            return false;
        }

        // Parse message
        return message.ParseFromArray(
            buffer.data() + sizeof(header),
            static_cast<int>(header.size)
        );
    }

private:
    // Helper to determine message type
    template<typename Message>
    static MessageType getMessageType(const Message& message) {
        if (dynamic_cast<const OrderRequest*>(&message)) return MessageType::ORDER;
        if (dynamic_cast<const OrderCancelRequest*>(&message)) return MessageType::ORDER_CANCEL;
        if (dynamic_cast<const OrderStatusRequest*>(&message)) return MessageType::ORDER_STATUS;
        if (dynamic_cast<const MarketDataRequest*>(&message)) return MessageType::MARKET_DATA;
        if (dynamic_cast<const SystemMessage*>(&message)) return MessageType::SYSTEM;
        if (dynamic_cast<const LoginRequest*>(&message)) return MessageType::AUTH;
        return MessageType::SYSTEM; // Default
    }
};

} // namespace TradingSystem 