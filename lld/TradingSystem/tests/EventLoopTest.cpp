#include <gtest/gtest.h>
#include "EventLoop.h"
#include <chrono>
#include <atomic>
#include <thread>
#include <iostream>

namespace TradingSystem {
namespace {

class EventLoopTest : public ::testing::Test {
protected:
    void SetUp() override {
        event_loop_.start();
    }

    void TearDown() override {
        event_loop_.stop();
    }

    EventLoop event_loop_;
};

TEST_F(EventLoopTest, BasicEventScheduling) {
    std::cout << "Testing basic event scheduling..." << std::endl;
    std::atomic<bool> event_executed{false};
    
    auto callback = [&event_executed]() {
        event_executed = true;
        std::cout << "Basic event executed." << std::endl;
    };
    
    event_loop_.scheduleEvent(callback, 1);
    
    // Wait for event to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    EXPECT_TRUE(event_executed);
    std::cout << "Basic event scheduling test passed." << std::endl;
}

TEST_F(EventLoopTest, EventPriority) {
    std::cout << "Testing event priority..." << std::endl;
    std::vector<int> execution_order;
    std::mutex order_mutex;
    
    auto callback1 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(1);
        std::cout << "Event 1 (highest priority) executed." << std::endl;
    };
    
    auto callback2 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(2);
        std::cout << "Event 2 (medium priority) executed." << std::endl;
    };
    
    auto callback3 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(3);
        std::cout << "Event 3 (lowest priority) executed." << std::endl;
    };
    
    // Schedule events with different priorities
    event_loop_.scheduleEvent(callback3, 3);  // Lowest priority
    event_loop_.scheduleEvent(callback1, 1);  // Highest priority
    event_loop_.scheduleEvent(callback2, 2);  // Medium priority
    
    // Wait for all events to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify execution order based on priority
    EXPECT_EQ(execution_order.size(), 3);
    EXPECT_EQ(execution_order[0], 1);  // Highest priority first
    EXPECT_EQ(execution_order[1], 2);  // Medium priority second
    EXPECT_EQ(execution_order[2], 3);  // Lowest priority last
    std::cout << "Event priority test passed." << std::endl;
}

TEST_F(EventLoopTest, EventCancellation) {
    std::cout << "Testing event cancellation..." << std::endl;
    std::atomic<bool> event_executed{false};
    
    auto callback = [&event_executed]() {
        event_executed = true;
        std::cout << "Cancelled event executed (should not happen)." << std::endl;
    };
    
    uint64_t event_id = event_loop_.scheduleEvent(callback, 1);
    event_loop_.cancelEvent(event_id);
    
    // Wait to ensure event would have been executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    EXPECT_FALSE(event_executed);
    std::cout << "Event cancellation test passed." << std::endl;
}

TEST_F(EventLoopTest, MultipleEvents) {
    std::cout << "Testing multiple events..." << std::endl;
    std::atomic<int> event_count{0};
    std::mutex count_mutex;
    
    auto callback = [&event_count, &count_mutex]() {
        std::lock_guard<std::mutex> lock(count_mutex);
        event_count++;
        std::cout << "Event executed. Total events: " << event_count << std::endl;
    };
    
    // Schedule multiple events
    for (int i = 0; i < 10; ++i) {
        event_loop_.scheduleEvent(callback, 1);
    }
    
    // Wait for all events to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    EXPECT_EQ(event_count, 10);
    std::cout << "Multiple events test passed." << std::endl;
}

TEST_F(EventLoopTest, EventExceptionHandling) {
    std::cout << "Testing event exception handling..." << std::endl;
    std::atomic<bool> event_executed{false};
    
    auto callback = [&event_executed]() {
        event_executed = true;
        std::cout << "Event executed with exception." << std::endl;
        throw std::runtime_error("Test exception");
    };
    
    // Event should be executed despite throwing an exception
    event_loop_.scheduleEvent(callback, 1);
    
    // Wait for event to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    EXPECT_TRUE(event_executed);
    std::cout << "Event exception handling test passed." << std::endl;
}

TEST_F(EventLoopTest, StopAndStart) {
    std::cout << "Testing stop and start functionality..." << std::endl;
    std::atomic<bool> event_executed{false};
    
    auto callback = [&event_executed]() {
        event_executed = true;
        std::cout << "Event executed after restart." << std::endl;
    };
    
    // Stop the event loop
    event_loop_.stop();
    
    // Schedule an event while stopped
    event_loop_.scheduleEvent(callback, 1);
    
    // Wait to ensure event would not be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_FALSE(event_executed);
    
    // Start the event loop again
    event_loop_.start();
    
    // Wait for event to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(event_executed);
    std::cout << "Stop and start test passed." << std::endl;
}

TEST_F(EventLoopTest, SamePriorityEvents) {
    std::cout << "Testing events with the same priority..." << std::endl;
    std::vector<int> execution_order;
    std::mutex order_mutex;
    
    auto callback1 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(1);
        std::cout << "Event 1 executed (same priority)." << std::endl;
    };
    
    auto callback2 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(2);
        std::cout << "Event 2 executed (same priority)." << std::endl;
    };
    
    // Schedule events with the same priority
    event_loop_.scheduleEvent(callback1, 1);
    event_loop_.scheduleEvent(callback2, 1);
    
    // Wait for all events to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify execution order (should be FIFO for same priority)
    EXPECT_EQ(execution_order.size(), 2);
    EXPECT_EQ(execution_order[0], 1);
    EXPECT_EQ(execution_order[1], 2);
    std::cout << "Same priority events test passed." << std::endl;
}

TEST_F(EventLoopTest, NegativePriorityEvents) {
    std::cout << "Testing events with negative priorities..." << std::endl;
    std::vector<int> execution_order;
    std::mutex order_mutex;
    
    auto callback1 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(1);
        std::cout << "Event 1 executed (negative priority)." << std::endl;
    };
    
    auto callback2 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(2);
        std::cout << "Event 2 executed (negative priority)." << std::endl;
    };
    
    // Schedule events with negative priorities
    event_loop_.scheduleEvent(callback1, -1);
    event_loop_.scheduleEvent(callback2, -2);
    
    // Wait for all events to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify execution order (should be based on priority)
    EXPECT_EQ(execution_order.size(), 2);
    EXPECT_EQ(execution_order[0], 2); // Higher priority (lower value) comes first
    EXPECT_EQ(execution_order[1], 1);
    std::cout << "Negative priority events test passed." << std::endl;
}

TEST_F(EventLoopTest, HighPriorityEvents) {
    std::cout << "Testing events with very high priorities..." << std::endl;
    std::vector<int> execution_order;
    std::mutex order_mutex;
    
    auto callback1 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(1);
        std::cout << "Event 1 executed (high priority)." << std::endl;
    };
    
    auto callback2 = [&execution_order, &order_mutex]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(2);
        std::cout << "Event 2 executed (high priority)." << std::endl;
    };
    
    // Schedule events with very high priorities
    event_loop_.scheduleEvent(callback1, 1000);
    event_loop_.scheduleEvent(callback2, 2000);
    
    // Wait for all events to be executed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Verify execution order (should be based on priority)
    EXPECT_EQ(execution_order.size(), 2);
    EXPECT_EQ(execution_order[0], 1); // Higher priority (lower value) comes first
    EXPECT_EQ(execution_order[1], 2);
    std::cout << "High priority events test passed." << std::endl;
}

} // namespace
} // namespace TradingSystem 