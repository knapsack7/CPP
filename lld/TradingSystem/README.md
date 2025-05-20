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