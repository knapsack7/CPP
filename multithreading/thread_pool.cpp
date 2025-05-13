class ThreadPool {
private:
    std::vector<std::thread> workers;  // Worker threads
    std::queue<std::function<void()>> tasks;  // Task queue
    std::mutex queue_mutex;  // Protects task queue
    std::condition_variable condition;  // Signals workers
    bool stop;  // Stop flag

public:
    ThreadPool(size_t threads) : stop(false) {
        // Create worker threads
        for(size_t i = 0; i < threads; ++i)
            workers.emplace_back([this] {
                while(true) {
                    std::function<void()> task;
                    {
                        // Wait for task or stop signal
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] { 
                            return stop || !tasks.empty(); 
                        });
                        
                        // Exit if stopped and no tasks
                        if(stop && tasks.empty()) return;
                        
                        // Get task from queue
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    // Execute task
                    task();
                }
            });
    }

    // Enqueue a task
    template<class F>
    std::future<typename std::result_of<F()>::type> enqueue(F&& f) {
        using return_type = typename std::result_of<F()>::type;
        
        // Create packaged task
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
        std::future<return_type> res = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &worker: workers)
            worker.join();
    }
};

/*
Key Concepts:
Task Queue: Stores pending tasks
Worker Threads: Continuously process tasks
Future/Promise: For getting results from tasks
*/


/* Use Cases
ThreadPool pool(4);  // 4 worker threads

// Submit task and get future
auto result = pool.enqueue([]() {
    return 42;
});

// Get result
int value = result.get();

*/