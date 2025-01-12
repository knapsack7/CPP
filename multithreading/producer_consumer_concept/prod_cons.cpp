#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::queue<int> dataQueue;          // Shared queue
std::mutex queueMutex;              // Mutex to protect the queue
std::condition_variable dataCond;  // Condition variable to notify waiting threads

bool finished = false;              // Flag to indicate when producer is done

// Producer function
void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            dataQueue.push(i);  // Add data to the queue
            std::cout << "Produced: " << i << std::endl;
        }
        dataCond.notify_one();  // Notify one waiting thread
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    }
    // Signal completion
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        finished = true;
    }
    dataCond.notify_all();  // Notify all waiting threads
}

// Consumer function
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        dataCond.wait(lock, [] { return !dataQueue.empty() || finished; });  // Wait for data

        if (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << data << std::endl;
        } else if (finished) {
            break;  // Exit if producer is done
        }
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
