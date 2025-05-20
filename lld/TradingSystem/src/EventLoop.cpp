#include "EventLoop.h"
#include <iostream>

namespace TradingSystem {

EventLoop::EventLoop() = default;

EventLoop::~EventLoop() {
    stop();
}

void EventLoop::start() {
    if (!running_) {
        running_ = true;
        event_thread_ = std::thread(&EventLoop::processEvents, this);
    }
}

void EventLoop::stop() {
    if (running_) {
        running_ = false;
        queue_condition_.notify_all();
        if (event_thread_.joinable()) {
            event_thread_.join();
        }
    }
}

EventLoop::EventId EventLoop::scheduleEvent(EventCallback callback, int priority) {
    EventId eventId = generateEventId();
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        event_queue_.push({eventId, std::move(callback), priority});
    }
    queue_condition_.notify_one();
    return eventId;
}

bool EventLoop::cancelEvent(EventId eventId) {
    std::lock_guard<std::mutex> lock(queue_mutex_);
    cancelled_events_[eventId] = true;
    return true;
}

void EventLoop::processEvents() {
    while (running_) {
        Event event;
        bool hasEvent = false;

        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            queue_condition_.wait(lock, [this] {
                return !running_ || !event_queue_.empty();
            });

            if (!running_) {
                break;
            }

            if (!event_queue_.empty()) {
                event = event_queue_.top();
                event_queue_.pop();
                hasEvent = true;
            }
        }

        if (hasEvent) {
            // Check if event was cancelled
            bool cancelled = false;
            {
                std::lock_guard<std::mutex> lock(queue_mutex_);
                cancelled = cancelled_events_[event.id];
                cancelled_events_.erase(event.id);
            }

            if (!cancelled) {
                try {
                    event.callback();
                } catch (const std::exception& e) {
                    std::cerr << "Error processing event: " << e.what() << std::endl;
                }
            }
        }
    }
}

EventLoop::EventId EventLoop::generateEventId() {
    return next_event_id_++;
}

} // namespace TradingSystem 