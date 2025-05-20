# Network-Based Trading System

A high-performance, network-based trading system implementing custom protocols and efficient order routing.

## Project Structure
```
TradingSystem/
├── include/           # Header files
├── src/              # Source files
├── tests/            # Test files
├── proto/            # Protocol buffer definitions
└── build/            # Build directory
```

## Architecture

The trading system is built as a simple client-server system. Here's how it works:

- **Client:** A user connects to the system using a client. The client sends requests (like placing an order or subscribing to market data) to the server.
- **Server:** The server receives these requests, processes them, and sends back responses. It also broadcasts real-time market data to all connected clients.
- **Order Router:** When a client places an order, the server sends it to the Order Router, which processes the order and updates its status.
- **Market Data Stream:** The server also manages a Market Data Stream, which sends real-time updates (like price changes) to all clients that have subscribed.
- **Protocol Layer:** All messages between the client and server are converted into a compact format (using Protocol Buffers) so they can be sent quickly over the network.

**Architecture Diagram:**

```
+-------------------+         +-------------------+
|    Client(s)      | <------>|      Server       |
|-------------------|   TCP   |-------------------|
| - Trading UI/API  |<------->| - Connection Mgr  |
| - Order Requests  |         | - Order Router    |
| - Market Data Sub |         | - Market Data     |
+-------------------+         | - Protocol Layer  |
                             +-------------------+
                                    |
                                    v
                          +---------------------+
                          |  Market Data Stream |
                          +---------------------+
                                    |
                                    v
                          +---------------------+
                          |   Order Router      |
                          +---------------------+
```

**How It Works:**

1. **Client Sends a Request:** The client sends a request (like placing an order) to the server.
2. **Server Processes the Request:** The server receives the request, converts it from the compact format, and sends it to the right part of the system (like the Order Router).
3. **Order Router or Market Data Stream:** The request is processed, and a response is generated.
4. **Server Sends a Response:** The server sends the response back to the client.
5. **Real-Time Updates:** For market data, the server broadcasts updates to all clients that have subscribed.

This design makes the system fast, reliable, and easy to understand.

## Event Loop Implementation

The Event Loop is a crucial component that manages asynchronous events and tasks in the trading system. Here's how to implement it:

### 1. Event Loop Structure
```cpp
class EventLoop {
private:
    std::priority_queue<Event, std::vector<Event>, EventComparator> event_queue_;
    std::atomic<bool> running_;
    std::mutex mutex_;
    std::condition_variable cv_;
};
```

### 2. Event Class Definition
```cpp
struct Event {
    int64_t priority;      // Higher number = higher priority
    std::function<void()> callback;
    std::chrono::steady_clock::time_point scheduled_time;
};
```

### 3. Implementation Steps

1. **Initialize Event Loop**
   ```cpp
   void EventLoop::start() {
       running_ = true;
       while (running_) {
           processEvents();
       }
   }
   ```

2. **Schedule Events**
   ```cpp
   void EventLoop::scheduleEvent(Event event) {
       std::lock_guard<std::mutex> lock(mutex_);
       event_queue_.push(event);
       cv_.notify_one();
   }
   ```

3. **Process Events**
   ```cpp
   void EventLoop::processEvents() {
       std::unique_lock<std::mutex> lock(mutex_);
       if (event_queue_.empty()) {
           cv_.wait(lock);
           return;
       }
       
       Event event = event_queue_.top();
       event_queue_.pop();
       lock.unlock();
       
       event.callback();
   }
   ```

4. **Stop Event Loop**
   ```cpp
   void EventLoop::stop() {
       running_ = false;
       cv_.notify_all();
   }
   ```

### 4. Usage Example
```cpp
EventLoop eventLoop;

// Schedule a high-priority event
Event highPriorityEvent{
    .priority = 100,
    .callback = []() { /* handle high priority task */ },
    .scheduled_time = std::chrono::steady_clock::now()
};
eventLoop.scheduleEvent(highPriorityEvent);

// Schedule a low-priority event
Event lowPriorityEvent{
    .priority = 10,
    .callback = []() { /* handle low priority task */ },
    .scheduled_time = std::chrono::steady_clock::now()
};
eventLoop.scheduleEvent(lowPriorityEvent);
```

### 5. Best Practices

1. **Priority Management**
   - Use clear priority levels
   - Document priority ranges
   - Consider priority inheritance

2. **Error Handling**
   - Catch exceptions in callbacks
   - Log errors appropriately
   - Implement retry mechanisms

3. **Performance Optimization**
   - Use efficient data structures
   - Minimize lock contention
   - Implement event batching

4. **Testing**
   - Unit test event scheduling
   - Test priority ordering
   - Verify event execution
   - Test error handling

### 6. Event Types: Solicited vs Unsolicited

In the trading system, events can be classified into two main categories:

#### Solicited Events
These are events that are triggered in response to a specific client request or action.

Examples:
```cpp
// 1. Order Placement Event (Solicited)
Event orderPlacementEvent{
    .priority = 100,
    .callback = [&]() {
        // Process order placement request
        Order order = client.getPendingOrder();
        risk_manager.validateOrder(order);
        order_router.processOrder(order);
    },
    .scheduled_time = std::chrono::steady_clock::now()
};

// 2. Market Data Subscription Event (Solicited)
Event subscriptionEvent{
    .priority = 80,
    .callback = [&]() {
        // Process market data subscription request
        std::string symbol = client.getSubscriptionSymbol();
        market_data_stream.addSubscriber(symbol, client);
    },
    .scheduled_time = std::chrono::steady_clock::now()
};
```

#### Unsolicited Events
These are events that occur automatically or are triggered by the system without a direct client request.

Examples:
```cpp
// 1. Market Data Update Event (Unsolicited)
Event marketDataEvent{
    .priority = 90,
    .callback = [&]() {
        // Broadcast market data updates to all subscribers
        MarketData data = market_data_stream.getLatestData();
        for (auto& subscriber : market_data_stream.getSubscribers()) {
            subscriber->onMarketDataUpdate(data);
        }
    },
    .scheduled_time = std::chrono::steady_clock::now()
};

// 2. Risk Limit Check Event (Unsolicited)
Event riskCheckEvent{
    .priority = 95,
    .callback = [&]() {
        // Periodic risk limit monitoring
        for (auto& client : risk_manager.getActiveClients()) {
            if (risk_manager.checkDailyLimit(client)) {
                notifyRiskLimitBreach(client);
            }
        }
    },
    .scheduled_time = std::chrono::steady_clock::now() + std::chrono::minutes(5)
};
```

#### Implementation Considerations

1. **Priority Assignment**
   - Solicited events typically have higher priority
   - Unsolicited events may have lower priority unless critical
   - System health checks should have highest priority

2. **Error Handling**
   - Solicited events require immediate error feedback to clients
   - Unsolicited events should log errors and retry if necessary
   - System events should have robust error recovery

3. **Resource Management**
   - Solicited events should have timeout mechanisms
   - Unsolicited events should be rate-limited
   - System events should monitor resource usage

4. **Testing Strategy**
   - Test solicited events with client request simulation
   - Test unsolicited events with time-based triggers
   - Verify event ordering and priority handling

## Features
- Client-server architecture
- Custom protocol implementation
- Order routing system
- Real-time market data streaming
- Connection pooling
- Load balancing
- Protocol buffer serialization

## Design Patterns Used

### 1. Client-Server Pattern
- Asynchronous server implementation
- Multiple client support
- Connection management
- Session handling

### 2. Protocol Design
- Custom binary protocol
- Protocol buffer integration
- Message framing
- Error handling

### 3. Reactor Pattern
- Event-driven architecture
- Non-blocking I/O
- Efficient event handling
- Scalable design

### 4. Connection Pool Pattern
- Resource reuse
- Connection management
- Load balancing
- Failover support

### 5. Observer Pattern
- Market data updates
- Order status notifications
- System events

## Network Programming Concepts

### 1. Socket Programming
- TCP/IP implementation
- Non-blocking sockets
- Connection pooling
- Error handling

### 2. Protocol Design
- Message framing
- Serialization/deserialization
- Protocol versioning
- Backward compatibility

### 3. Network Optimization
- Zero-copy operations
- Buffer management
- Connection pooling
- Load balancing

### 4. Security
- TLS/SSL support
- Authentication
- Authorization
- Encryption

## Protocol Buffer Definitions

### 1. Order Messages
```protobuf
message Order {
    string order_id = 1;
    string symbol = 2;
    double price = 3;
    int32 quantity = 4;
    OrderType type = 5;
    OrderSide side = 6;
}
```

### 2. Market Data Messages
```protobuf
message MarketData {
    string symbol = 1;
    double price = 2;
    int32 quantity = 3;
    int64 timestamp = 4;
}
```

### 3. System Messages
```protobuf
message SystemMessage {
    MessageType type = 1;
    string message = 2;
    int32 code = 3;
}
```

## Requirements
- C++17 or higher
- CMake 3.10 or higher
- Protocol Buffers
- Boost.Asio
- Google Test (for testing)

## Building the Project
```bash
mkdir build && cd build
cmake ..
make
```

## Running Tests
```bash
cd build
./TradingSystemTest
```

## Usage Example

### Server
```cpp
#include "Server.h"

int main() {
    TradingSystem::Server server("0.0.0.0", 8080);
    server.start();
    return 0;
}
```

### Client
```cpp
#include "Client.h"

int main() {
    TradingSystem::Client client("localhost", 8080);
    client.connect();
    
    // Place an order
    Order order;
    order.set_symbol("AAPL");
    order.set_price(150.0);
    order.set_quantity(100);
    order.set_type(OrderType::LIMIT);
    order.set_side(OrderSide::BUY);
    
    client.placeOrder(order);
    return 0;
}
```

## Performance Considerations

### 1. Network Optimization
- Zero-copy operations
- Buffer pooling
- Connection reuse
- Message batching

### 2. Protocol Efficiency
- Binary protocol
- Message compression
- Efficient serialization
- Protocol versioning

### 3. Scalability
- Connection pooling
- Load balancing
- Horizontal scaling
- Resource management

## Troubleshooting

### 1. Network Issues
- Connection timeouts
- Protocol errors
- Buffer overflows
- Resource exhaustion

### 2. Performance Issues
- Network latency
- Protocol overhead
- Resource contention
- Memory leaks

### 3. Security Issues
- Authentication failures
- Authorization errors
- Protocol attacks
- Data integrity

## Best Practices

### 1. Network Programming
- Error handling
- Resource management
- Protocol design
- Security implementation

### 2. Protocol Design
- Versioning
- Backward compatibility
- Error handling
- Message validation

### 3. Testing
- Unit tests
- Integration tests
- Load tests
- Security tests

## Future Improvements
- WebSocket support
- REST API integration
- Advanced order types
- Real-time analytics
- Machine learning integration
- Distributed deployment
- Cloud integration 

## Issues Solved

### 1. Protobuf Integration Issues
- Resolved architecture mismatch between Protobuf library and project
- Fixed linker errors related to undefined Protobuf symbols
- Updated Protobuf version from 3.20.3 to 5.29.3 for better compatibility
- Implemented proper CMake configuration for Protobuf linking

### 2. Server Connection Issues
- Fixed server binding issues by replacing "localhost" with "127.0.0.1"
- Implemented proper server startup and shutdown in test fixtures
- Added connection timeout handling
- Resolved "Accept error: Operation canceled" during server shutdown

### 3. Test Execution Issues
- Implemented proper test fixture setup and teardown
- Added server startup delay to ensure proper initialization
- Fixed concurrent test execution issues
- Ensured proper cleanup of resources after tests

### 4. Build System Issues
- Updated CMake configuration for proper dependency management
- Fixed Boost library warnings (CMP0167 policy)
- Implemented proper linking of all required libraries
- Added proper include paths for all dependencies

### 5. Thread Safety Issues
- Implemented proper mutex protection for shared resources
- Added atomic variables for thread-safe state management
- Implemented proper thread synchronization using condition variables
- Ensured thread-safe message handling in the server

### 6. Memory Management
- Implemented RAII for resource management
- Fixed potential memory leaks in connection handling
- Added proper cleanup in destructors
- Implemented smart pointers for automatic memory management

### 7. Error Handling
- Added comprehensive error handling for network operations
- Implemented proper exception handling
- Added logging for debugging purposes
- Improved error messages for better debugging 

# Trading System

A high-performance, real-time trading system implemented in C++.

## Features

- Real-time order processing with priority-based execution
- Event-driven architecture for efficient message handling
- Comprehensive risk management system
- Thread-safe operations with mutex protection
- Asynchronous I/O using Boost.Asio
- Protocol Buffers for efficient message serialization
- Unit tests with Google Test framework

## Architecture

### Core Components

1. **Client**
   - Handles client connections and message processing
   - Manages order submission and market data subscription
   - Implements asynchronous I/O operations

2. **Server**
   - Manages multiple client connections
   - Processes incoming orders and market data requests
   - Broadcasts market data updates to subscribed clients

3. **Order Router**
   - Routes orders to appropriate handlers
   - Implements priority-based order processing
   - Integrates with risk management system

4. **Risk Manager**
   - Validates orders against position limits
   - Enforces price limits for symbols
   - Tracks daily trading limits per client
   - Thread-safe position tracking

5. **Event Loop**
   - Manages event scheduling and execution
   - Supports priority-based event processing
   - Handles event cancellation
   - Exception-safe event execution

### Design Patterns

- Observer Pattern for market data updates
- Factory Pattern for message creation
- Strategy Pattern for order processing
- Singleton Pattern for global services

### Network Programming Concepts

- TCP/IP communication
- Asynchronous I/O operations
- Connection pooling
- Message framing and serialization

## Risk Management

The system implements comprehensive risk management through the `RiskManager` class:

- **Position Limits**: Enforces maximum position sizes per client and symbol
- **Price Limits**: Validates order prices against configured min/max limits
- **Daily Limits**: Tracks and enforces daily trading limits per client
- **Thread Safety**: All risk checks and updates are thread-safe

Example usage:
```cpp
// Set position limit for a client
risk_manager.setPositionLimit("client1", "AAPL", 1000);

// Set price limits for a symbol
risk_manager.setPriceLimit("AAPL", 100.0, 200.0);

// Set daily trading limit
risk_manager.setDailyLimit("client1", 100000.0);
```

## Event-Driven Architecture

The system uses an event-driven architecture through the `EventLoop` class:

- **Priority-based Execution**: Events are executed based on their priority
- **Event Scheduling**: Supports scheduling events with different priorities
- **Event Cancellation**: Allows canceling scheduled events
- **Exception Handling**: Safely handles exceptions during event execution

Example usage:
```cpp
// Schedule a high-priority event
event_loop.scheduleEvent([]() {
    // Handle critical operation
}, 1);  // Priority 1 (highest)

// Schedule a low-priority event
event_loop.scheduleEvent([]() {
    // Handle background task
}, 3);  // Priority 3 (lowest)
```

## Requirements

- C++17 or later
- Boost 1.74.0 or later
- Protocol Buffers 3.15.0 or later
- CMake 3.10 or later
- Google Test (for testing)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Testing

```bash
cd build
ctest
```

## Usage Examples

### Starting the Server

```cpp
Server server("localhost", 8080);
server.start();
```

### Creating a Client

```cpp
Client client("localhost", 8080);
client.connect();
```

### Submitting an Order

```cpp
trading::Order order;
order.set_client_id("client1");
order.set_symbol("AAPL");
order.set_quantity(100);
order.set_price(150.0);
client.submitOrder(order);
```

### Subscribing to Market Data

```cpp
client.subscribeMarketData("AAPL", [](const MarketData& data) {
    // Handle market data update
});
```

## Performance Considerations

- Use of asynchronous I/O for efficient network operations
- Thread-safe operations with minimal locking
- Priority-based event processing
- Efficient message serialization with Protocol Buffers

## Troubleshooting

1. **Connection Issues**
   - Check server address and port
   - Verify firewall settings
   - Check network connectivity

2. **Build Issues**
   - Ensure all dependencies are installed
   - Check CMake version
   - Verify compiler version

3. **Runtime Issues**
   - Check log files
   - Verify configuration settings
   - Monitor system resources

## Best Practices

1. **Error Handling**
   - Use try-catch blocks for exception handling
   - Log errors with appropriate context
   - Implement graceful error recovery

2. **Resource Management**
   - Use RAII for resource management
   - Implement proper cleanup in destructors
   - Monitor memory usage

3. **Thread Safety**
   - Use mutexes for shared resource access
   - Implement proper synchronization
   - Avoid deadlocks

## Future Improvements

1. **Performance**
   - Implement connection pooling
   - Add message compression
   - Optimize serialization

2. **Features**
   - Add support for more order types
   - Implement order matching engine
   - Add market data persistence

3. **Monitoring**
   - Add performance metrics
   - Implement health checks
   - Add monitoring dashboard

## Issues Solved

1. **Protobuf Integration**
   - Resolved architecture mismatch issues
   - Fixed linker errors with proper library linking
   - Implemented efficient message serialization

2. **Server Connection**
   - Fixed binding issues with proper address handling
   - Implemented connection timeout handling
   - Added connection state management

3. **Test Execution**
   - Resolved test fixture setup issues
   - Fixed concurrent test execution problems
   - Implemented proper test cleanup

4. **Build System**
   - Fixed dependency management
   - Resolved library linking issues
   - Implemented proper CMake configuration

5. **Thread Safety**
   - Added mutex protection for shared resources
   - Implemented atomic variables for state management
   - Fixed race conditions in order processing

6. **Memory Management**
   - Implemented RAII for resource management
   - Added smart pointers for dynamic objects
   - Fixed memory leaks in connection handling

7. **Error Handling**
   - Added comprehensive error handling
   - Implemented proper exception handling
   - Added logging for debugging

8. **Risk Management**
   - Implemented position limit tracking
   - Added price limit validation
   - Implemented daily limit monitoring

9. **Event Processing**
   - Added priority-based event scheduling
   - Implemented event cancellation
   - Added exception-safe event execution 