#pragma once

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <memory>
#include <unordered_map>

namespace TradingSystem {

class EventLoop {
public:
    using EventCallback = std::function<void()>;
    using EventId = uint64_t;

    EventLoop();
    ~EventLoop();

    // Prevent copying
    EventLoop(const EventLoop&) = delete;
    EventLoop& operator=(const EventLoop&) = delete;

    // Start and stop the event loop
    void start();
    void stop();

    // Schedule an event to be executed
    EventId scheduleEvent(EventCallback callback, int priority = 0);
    
    // Cancel a scheduled event
    bool cancelEvent(EventId eventId);

    // Check if the event loop is running
    bool isRunning() const { return running_; }

private:
    struct Event {
        EventId id;
        EventCallback callback;
        int priority;
    };

    struct EventComparator {
        bool operator()(const Event& a, const Event& b) const {
            return a.priority > b.priority; // Higher priority (lower value) comes first
        }
    };

    void processEvents();
    EventId generateEventId();

    std::priority_queue<Event, std::vector<Event>, EventComparator> event_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_condition_;
    std::atomic<bool> running_{false};
    std::thread event_thread_;
    std::atomic<EventId> next_event_id_{0};
    std::unordered_map<EventId, bool> cancelled_events_;
};

} // namespace TradingSystem 