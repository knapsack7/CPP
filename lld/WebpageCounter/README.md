# Webpage Counter - Thread-Safe Implementation

## Overview
This is a thread-safe implementation of a webpage visit counter that can handle multiple concurrent accesses. The implementation demonstrates various C++ concepts and best practices for concurrent programming.

## Issues Encountered and Solutions

### 1. Logger Management Issue
**Problem:**
- Initial implementation used raw pointers for logger
- Logger was being destroyed after constructor completion
- Led to segmentation faults when trying to use the logger

**Solution:**
- Used `std::unique_ptr<ILogger>` for proper ownership
- Ensured logger lifetime matches the WebpageCounter lifetime
- Implemented RAII (Resource Acquisition Is Initialization) principles

**Key Concept:**
- RAII: A programming idiom where resource acquisition and release are bound to object lifetime
- `std::unique_ptr`: Smart pointer that ensures single ownership and automatic cleanup

### 2. Atomic Operations Issue
**Problem:**
- Initial implementation used `std::vector` for atomic integers
- Atomic types are not copyable or movable
- Led to compilation errors during vector operations

**Solution:**
- Used `std::array` instead of `std::vector` for atomic integers
- Properly initialized atomic values with `store(0, std::memory_order_relaxed)`
- Consistent memory ordering across all operations

**Key Concept:**
- `std::atomic`: Provides atomic operations on variables
- Memory Ordering: Controls how atomic operations are synchronized
- `std::array`: Fixed-size container that doesn't require copy/move operations

### 3. Container Choice and Cache Locality
**Problem:**
- Initial implementation used `std::vector` for storage
- Dynamic allocation led to poor cache locality
- Unnecessary heap allocation for fixed-size data

**Solution:**
- Used `std::array` for fixed-size storage
- Leveraged stack allocation for better performance
- Improved cache locality with contiguous memory layout

**Key Concept:**
- Cache Locality: Keeping related data close in memory for faster access
- Stack vs Heap: Stack allocation is faster and more cache-friendly
- Memory Layout: Contiguous memory access patterns improve performance
- Fixed-size Containers: Using appropriate containers for known sizes

### 4. Mutex Handling Issue
**Problem:**
- Initial implementation had potential deadlocks
- Mutexes weren't properly initialized
- Led to segmentation faults and program hangs

**Solution:**
- Used `std::array` of `std::unique_ptr<std::mutex>` for proper mutex management
- Added proper mutex validation checks
- Implemented non-blocking locks in batch operations

**Key Concept:**
- Mutex: Mutual exclusion object for thread synchronization
- Deadlock Prevention: Using consistent lock ordering and non-blocking locks
- Smart Pointers: Managing mutex lifetime automatically

### 5. Batch Operations Issue
**Problem:**
- Batch operations could deadlock
- Same mutex could be locked multiple times
- Program would hang during batch operations

**Solution:**
- Added duplicate removal to prevent double-locking
- Used `std::try_to_lock` to prevent deadlocks
- Separated lock acquisition from increment operations

**Key Concept:**
- Deadlock: A situation where two or more threads are blocked forever
- Lock Ordering: Consistent order of acquiring locks to prevent deadlocks
- Non-blocking Locks: Using try_lock to prevent indefinite waiting

### 6. Error Handling Issue
**Problem:**
- Error messages weren't descriptive enough
- Inconsistent error handling across operations
- Difficult to debug issues

**Solution:**
- Added more descriptive error messages
- Implemented proper validation of all operations
- Consistent error handling across the codebase

**Key Concept:**
- Exception Handling: Using try-catch blocks for error management
- Validation: Checking preconditions before operations
- Error Messages: Clear and descriptive error information

## Key Features
1. Thread-safe operations
2. Deadlock prevention
3. Proper resource management
4. Clear error handling
5. Efficient atomic operations

## Usage Example
```cpp
// Create configuration
Config config;
config.enableLogging = true;
config.useAtomicOperations = true;

// Create logger
auto logger = std::make_unique<Logger>();

// Initialize counter
WebpageCounter counter(2, std::move(logger), config);

// Increment visits
counter.incrementVisitCount(0);
counter.incrementVisitCount(1);

// Batch increment
counter.batchIncrement({1, 1, 0});

// Get visit counts
int count0 = counter.getVisitCount(0);
int count1 = counter.getVisitCount(1);
```

## Compilation
```bash
g++ WebpageCounter.cpp -o WebpageCounter
```

## Learning Outcomes
1. Understanding of thread safety in C++
2. Proper resource management with RAII
3. Atomic operations and memory ordering
4. Mutex usage and deadlock prevention
5. Error handling in concurrent programs

## Future Improvements
1. Add timeout mechanism for locks
2. Implement more sophisticated logging
3. Add performance metrics
4. Support for dynamic page count
5. Add unit tests for concurrent operations 

## Object-Oriented Programming Concepts Used

### 1. Encapsulation
- Private member variables (`visitCounts`, `mutexes`, `logger`, etc.)
- Public interface methods (`incrementVisitCount`, `getVisitCount`, etc.)
- Data hiding through access specifiers
- Controlled access to internal state

### 2. Inheritance
- `InvalidPageIndex` inherits from `std::runtime_error`
- `Logger` class inherits from `ILogger` interface
- Demonstrates interface inheritance for logging functionality

### 3. Polymorphism
- `ILogger` interface with virtual methods
- `Logger` class implementing the interface
- Runtime polymorphism through virtual function calls
- Ability to swap different logger implementations

### 4. Abstraction
- `ILogger` interface abstracting logging functionality
- `Config` structure abstracting configuration parameters
- `Metrics` structure abstracting performance tracking
- Clear separation of concerns

### 5. RAII (Resource Acquisition Is Initialization)
- Smart pointers (`std::unique_ptr`) for resource management
- Automatic cleanup of resources
- Exception-safe resource handling
- Proper lifetime management of logger and mutexes

## Design Patterns Used

### 1. Strategy Pattern
- Logging strategy through `ILogger` interface
- Different logger implementations can be swapped
- Runtime configuration of logging behavior
- Example:
```cpp
class ILogger {
    virtual void log(const std::string& message) = 0;
};
class Logger : public ILogger {
    void log(const std::string& message) override;
};
```

### 2. Singleton Pattern (Implicit)
- Configuration structure as a single instance
- Shared configuration across the application
- Centralized configuration management

### 3. Observer Pattern (Implicit)
- Metrics tracking as an observer of operations
- Automatic updates to metrics on operations
- Separation of core functionality from monitoring

### 4. Factory Method Pattern
- Creation of logger instances
- Encapsulated object creation
- Example:
```cpp
auto logger = std::make_unique<Logger>();
```

### 5. RAII Pattern
- Resource management through constructors and destructors
- Automatic cleanup of resources
- Exception-safe resource handling
- Example:
```cpp
std::unique_ptr<ILogger> logger;
std::array<std::unique_ptr<std::mutex>, MAX_PAGES> mutexes;
```

## SOLID Principles Applied

### 1. Single Responsibility Principle
- Each class has a single responsibility
- `WebpageCounter` handles counting
- `Logger` handles logging
- `Metrics` handles tracking

### 2. Open/Closed Principle
- Open for extension through interfaces
- Closed for modification
- New logger implementations can be added
- New metrics can be added

### 3. Liskov Substitution Principle
- `Logger` can be substituted for `ILogger`
- Derived classes maintain contract of base class
- Polymorphic behavior works correctly

### 4. Interface Segregation Principle
- `ILogger` interface is focused and minimal
- Clients only depend on methods they use
- Clean and specific interfaces

### 5. Dependency Inversion Principle
- High-level modules depend on abstractions
- `WebpageCounter` depends on `ILogger` interface
- Not on concrete `Logger` implementation 


## Development Errors and Solutions

### 1. Mutex Double-Locking Issue
**Problem:**
- Initial implementation had potential for double-locking mutexer double-locking mutexe locked multiple timess
- Same mutex could be locked multiple times ogram hangs

**Solution:**
- Added duplicate removal iLed to deadlocks and program hangs

**Solution:**
- Added duplicate removal iis locked only once
- Implemented proper mutex validation checks

**Key Concept:**
- Deadlock: A situation where a tn batch operations
- Used `std::sort` and `std::unique` to ensure each mutex is locked only once
- Implemented proper mutex validation checks

**Key Concept:**
- Deadlock: A situation where a t2. Atomic Operations Issue
**Problem:**
- Initial implementation used `std::vector`  that it holds
- Mutex Locking: Each mutex should be locked only once by the same thread
- Batch Operations: Need special handling to prevent multiple locks

### 2. Atomic Operations Issue
**Problem:**
- Initial implementation used `std::vector` , std::memory_order_relaxed)`
- Consistent memory ordering across all operationsfor atomic integers
- Atomic types are not copyable or movable
- Led to compilation errors during vector operations

**Solution:**
- Used `std::array` instead of `std::vector` for atomic integers
- Properly initialized atomic values with `store(0, std::memory_order_relaxed)`
- Consistent memory ordering across all operationsions on variables
- Memory Ordering: Controls how atomic operations are synchronized
- `std::array`: Fixed-size container that doesn't require copy/move operations

### 3. Container Choice and Cache Locality
**rmance
- Improved cache locality with contiguous memory layout

**Key Concept:**
- Cache Locality: Keeping rn used `std::vector` for storage
- Dynamic allocation led to poor cache locality
- Unnecessary heap allocation for fixed-size data

**Solution:**
- Used `std::array` for fixed-size storage
- Leveraged stack allocation for better performance
- Improved cache locality with contiguous memory layout

**Key Concept:**
- Cache Locality: Keeping r- Led to segmentatioelated data close in memory for faster access
- Stack vs Heap: Stack allocation is faster and more cache-friendly
- Memory Layout: Contiguous memory access patterns improve performance

### 4. Logger Management Issue
**Problem:**
- Initial implementation used raw pointers for logger
- Logger was being destroyed after constructor completion
- Led to segmentatio::unique_ptr`: Smart pointer that ensures single ownership and aut to use the logger

**Solution:**
- Used `std::unique_ptr<ILogger>` for proper ownership
- Ensured logger lifetime matches the WebpageCounter lifetime
- Implemented RAII (Resource Acquisition Is Initialization) principles

**Key Concept:**
- RAII: A programming idiom where resource acquisition and release are bound to object lifetime
- `std::unique_ptr`: Smart pointer that ensures single ownership and autement
- Validation: Checking preconditions before operations
- Error Messages: Clear and descriptive errssages
- Implemented proper validation of all operations
- Consistent error handling across the codebase

**Key Concept:**
- Exception Handling: Using try-catch blocks for error management
- Validation: Checking preconditions before operations
- Error Messages: Clear and descriptive errnding the design decisions made
3. Learning from the challenges faced
4. Avoiding similar issues in future development

### Batch Increment Efficiency

**Why Batch Increment is More Efficient Than Single Increment**

1. **Reduced Lock Operations**
```cpp
// Single Increment (3 pages):
incrementVisitCount(0);  // Lock 0, increment, unlock 0
incrementVisitCount(1);  // Lock 1, increment, unlock 1
incrementVisitCount(2);  // Lock 2, increment, unlock 2
// Total: 6 lock/unlock operations

// Batch Increment (3 pages):
batchIncrement({0, 1, 2});
// Lock 0, 1, 2 once
// Perform all increments
// Unlock 0, 1, 2 once
// Total: 6 lock/unlock operations
```

2. **Atomic Operation Optimization**
```cpp
// Single Increment:
visitCounts[0].fetch_add(1);  // Atomic operation
visitCounts[1].fetch_add(1);  // Atomic operation
visitCounts[2].fetch_add(1);  // Atomic operation
// Each increment is a separate atomic operation

// Batch Increment:
// All increments happen while holding the lock
// Can use relaxed memory ordering
// Better cache utilization
```

3. **Cache Locality Benefits**
```cpp
// Single Increment:
// Each increment might cause cache misses
// Memory access pattern is scattered

// Batch Increment:
// All increments happen in sequence
// Better cache locality
// Reduced memory access overhead
```

4. **Thread Synchronization**
```cpp
// Single Increment:
// Each increment requires thread synchronization
// More context switches
// More thread scheduling overhead

// Batch Increment:
// Single synchronization point
// Fewer context switches
// Better thread scheduling
```

5. **Performance Metrics**
- Reduced number of lock/unlock operations
- Better cache utilization
- Fewer thread synchronizations
- More efficient memory access patterns
- Reduced overhead in thread scheduling

6. **Real-World Impact**
```cpp
// Example: Incrementing 1000 pages
// Single Increment:
// - 2000 lock/unlock operations
// - 1000 atomic operations
// - 1000 potential cache misses

// Batch Increment:
// - 2000 lock/unlock operations
// - 1000 atomic operations
// - Better cache locality
// - Single synchronization point
```

7. **Best Practices for Batch Operations**
- Use batch operations for multiple increments
- Remove duplicates to prevent double-locking
- Lock all required mutexes at once
- Perform all increments while holding locks
- Unlock all mutexes at once
