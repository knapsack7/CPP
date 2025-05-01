
#include <iostream>                  // For console output
#include <thread>                    // For std::thread
#include <mutex>                     // For std::mutex, std::unique_lock
#include <atomic>                    // For std::atomic
#include <condition_variable>        // For std::condition_variable
#include <queue>                     // For std::queue
#include <vector>                    // For std::vector
#include <chrono>                    // For std::chrono::milliseconds

std::mutex mtx;                      // Mutex for protecting shared buffer
std::condition_variable cv;         // Condition variable for synchronization
std::queue<int> buffer;             // Shared buffer for producer-consumer
const int MAX_SIZE = 5;             // Maximum buffer size
std::atomic<int> atomicCounter(0);  // Atomic counter to track produced items
thread_local int threadLocalID = 0; // Thread-local ID for each consumer

const int TOTAL_ITEMS_TO_PRODUCE = 15;  // Smooth termination condition

// Producer thread function
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait if buffer is full
        cv.wait(lock, []() { return buffer.size() < MAX_SIZE; });

        int item = id * 100 + i;
        buffer.push(item);  // Produce item
        std::cout << "[Producer " << id << "] Produced: " << item << "\n";

        atomicCounter.fetch_add(1);  // Safely increment atomic counter
        cv.notify_all();  // Notify all waiting threads

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate delay
    }
}

// Consumer thread function
void consumer(int id) {
    threadLocalID = id;

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until buffer has at least one item
        cv.wait(lock, []() { return !buffer.empty() || atomicCounter.load() >= TOTAL_ITEMS_TO_PRODUCE; });

        if (!buffer.empty()) {
            int value = buffer.front();
            buffer.pop();  // Consume item

            std::cout << "[Consumer " << threadLocalID << "] Consumed: " << value << "\n";
            cv.notify_all();  // Notify producers if needed

            lock.unlock();  // Unlock before sleeping
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        } else if (atomicCounter.load() >= TOTAL_ITEMS_TO_PRODUCE) {
            // Exit if all items have been produced and buffer is empty
            break;
        }
    }
}

int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Launch 3 producer threads
    for (int i = 1; i <= 3; ++i)
        producers.emplace_back(producer, i);

    // Launch 2 consumer threads
    for (int i = 1; i <= 2; ++i)
        consumers.emplace_back(consumer, i);

    // Wait for all producers to finish
    for (auto &p : producers) p.join();

    // Wait for all consumers to finish
    for (auto &c : consumers) c.join();

    std::cout << "Final count of produced items: " << atomicCounter.load() << std::endl;
    return 0;
}
