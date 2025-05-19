# Order Book System

A C++ implementation of a basic order book system that demonstrates key C++ concepts including RAII, smart pointers, and STL containers.

## Project Structure
```
OrderBookSystem/
├── include/           # Header files
│   ├── Order.h       # Order class definition
│   ├── OrderBook.h   # OrderBook class definition
│   └── MarketData.h  # Market data handling
├── src/              # Source files
│   ├── Order.cpp
│   ├── OrderBook.cpp
│   └── MarketData.cpp
├── tests/            # Unit tests
│   └── OrderBookTest.cpp
├── CMakeLists.txt    # Build configuration
└── README.md         # This file
```

## Features
- Order entry and matching system
- Price-time priority implementation
- Basic market data handling
- RAII principles
- Smart pointer usage
- STL container utilization

## Design Principles and OOP Concepts

### SOLID Principles
1. **Single Responsibility Principle (SRP)**
   - `Order` class handles only order-related data and operations
   - `OrderBook` class manages order matching and book maintenance
   - `MarketData` class focuses on trade recording and market statistics

2. **Open/Closed Principle (OCP)**
   - System is open for extension (new order types, matching algorithms)
   - Core functionality is closed for modification
   - Easy to add new market data metrics without changing existing code

3. **Interface Segregation Principle (ISP)**
   - Clean separation between order management and market data interfaces
   - Each class exposes only necessary methods to clients

4. **Dependency Inversion Principle (DIP)**
   - High-level modules (OrderBook) don't depend on low-level modules
   - Dependencies are managed through abstractions

### Object-Oriented Concepts
1. **Encapsulation**
   - Private data members with public getters/setters
   - Implementation details hidden from clients
   - Controlled access to internal state

2. **Abstraction**
   - Clear separation of concerns between components
   - Abstract interfaces for order matching and market data
   - Simplified client interaction with complex internal operations

3. **Inheritance and Polymorphism**
   - Extensible design for different order types
   - Virtual methods for customizing behavior
   - Interface-based programming

4. **Composition**
   - OrderBook composed of Orders
   - MarketData composed of Trades
   - Strong ownership semantics using smart pointers

### Modern C++ Features
1. **RAII (Resource Acquisition Is Initialization)**
   - Automatic resource management
   - Smart pointer usage for memory safety
   - Exception-safe design

2. **Move Semantics**
   - Efficient transfer of resources
   - Move constructors and assignment operators
   - R-value references

3. **STL Containers and Algorithms**
   - `std::map` for price levels
   - `std::queue` for order matching
   - `std::vector` for market data storage

## Requirements
- C++17 or higher
- CMake 3.10 or higher
- GTest (for unit tests)

## Building the Project
```bash
mkdir build
cd build
cmake ..
make
```

## Running Tests
```bash
cd build
./tests/OrderBookTest
```

## Usage Example
```cpp
#include "OrderBook.h"

int main() {
    OrderBook book;
    
    // Add orders
    book.addOrder(Order(100.0, 10, OrderType::BUY));
    book.addOrder(Order(99.0, 5, OrderType::SELL));
    
    // Match orders
    book.matchOrders();
    
    return 0;
}
```

## Troubleshooting & Lessons Learned

During the development and testing of this project, several real-world C++ and build system issues were encountered and resolved. Below are the main challenges and the steps taken to fix them:

### 1. Range-based for loop with std::queue and std::unique_ptr
**Problem:**  
Attempting to use range-based for loops directly on `std::queue<std::unique_ptr<T>>` caused compilation errors, as `std::queue` does not support iteration and `std::unique_ptr` is non-copyable.

**Resolution:**  
- Switched to iterating by copying the queue and popping elements, or (for efficiency and clarity) maintained separate volume tracking maps for each price level.
- This allowed for safe and efficient volume calculations without modifying the original queues or violating unique ownership semantics.

---

### 2. Linker Errors in GTest Executable
**Problem:**  
The test executable failed to link due to missing symbols for implementation functions (e.g., `OrderBook::OrderBook::addOrder`).  
This happened because the test target was not linked with the main source files.

**Resolution:**  
- Updated `CMakeLists.txt` to link the test executable with all implementation source files (except `main.cpp`).
- Used `list(REMOVE_ITEM SOURCES src/main.cpp)` to ensure the test executable does not include the main program entry point, avoiding duplicate symbol errors.

---

### 3. Namespace and Type Ambiguity
**Problem:**  
Ambiguous references to types like `OrderBook`, `MarketData`, and `Trade` in the test file, leading to compilation errors.

**Resolution:**  
- Used fully qualified names (e.g., `OrderBook::OrderBook`, `OrderBook::Order`, `OrderBook::MarketData`, `OrderBook::Trade`) in the test code to resolve ambiguity and ensure correct type usage.

---

### 4. General Build Steps for a Clean Build
If you encounter build or linker errors, follow these steps:
```bash
# From the project root (lld/OrderBookSystem)
rm -rf build
mkdir build
cd build
cmake ..
make
./OrderBookTest   # To run all tests
./orderbook       # To run the main program
```

---

**These steps and lessons are typical in real-world C++ projects, especially when using modern C++ features, smart pointers, and integrating with CMake and GoogleTest. If you encounter similar issues, refer to this section for guidance!** 