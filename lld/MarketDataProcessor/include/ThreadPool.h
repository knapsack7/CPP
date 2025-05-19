#pragma once

#include "Queue.h"
#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <type_traits>
#include <atomic>

namespace MarketData {

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads) : stop_(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    auto task = tasks_.pop();
                    if (!task) {
                        break;
                    }
                    (*task)();
                }
            });
        }
    }

    ~ThreadPool() {
        stop();
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // Prevent copying
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Prevent moving
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type> {
        using return_type = typename std::invoke_result<F, Args...>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        tasks_.push([task]() { (*task)(); });
        return res;
    }

    void stop() {
        stop_ = true;
        tasks_.stop();
    }

private:
    std::vector<std::thread> workers_;
    Queue<std::function<void()>> tasks_;
    std::atomic<bool> stop_;
};

} // namespace MarketData 