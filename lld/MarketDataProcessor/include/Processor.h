#pragma once

#include "MarketData.h"
#include "ThreadPool.h"
#include <unordered_map>
#include <mutex>
#include <memory>

namespace MarketData {

class Processor {
public:
    explicit Processor(size_t numThreads) : threadPool_(numThreads) {}

    ~Processor() {
        stop();
    }

    // Prevent copying
    Processor(const Processor&) = delete;
    Processor& operator=(const Processor&) = delete;

    // Prevent moving
    Processor(Processor&&) = delete;
    Processor& operator=(Processor&&) = delete;

    void start() {
        running_ = true;
    }

    void stop() {
        running_ = false;
        threadPool_.stop();
    }

    void addData(const MarketData& data) {
        if (!running_) return;

        threadPool_.submit([this, data] {
            std::lock_guard<std::mutex> lock(mutex_);
            auto& stats = stats_[data.symbol];
            stats.update(data);
        });
    }

    double getLastPrice(const std::string& symbol) const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = stats_.find(symbol);
        return it != stats_.end() ? it->second.getLastPrice() : 0.0;
    }

    int getTotalVolume(const std::string& symbol) const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = stats_.find(symbol);
        return it != stats_.end() ? it->second.getTotalVolume() : 0;
    }

private:
    ThreadPool threadPool_;
    std::unordered_map<std::string, MarketDataStats> stats_;
    mutable std::mutex mutex_;
    std::atomic<bool> running_{false};
};

} // namespace MarketData 