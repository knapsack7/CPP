#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer; // Shared buffer
const int maxBufferSize = 5;
bool done = false; // Flag to indicate when to stop

void producer() {
    for (int i = 0; i < 10; ++i) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            // Wait until there's space in the buffer
            cv.wait(lock, [] { return buffer.size() < maxBufferSize; });
            buffer.push(i); // Produce an item
            std::cout << "Produced: " << i << std::endl;
        }
        cv.notify_one(); // Notify one waiting consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate production time
    }

    // Signal that production is done
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true; // Set the done flag to true
    }
    cv.notify_all(); // Notify all consumers to check for completion
}

void consumer(int id) {
    while (true) {
        int item;
        {
            std::unique_lock<std::mutex> lock(mtx);
            // Wait until there is an item to consume or production is done
            cv.wait(lock, [] { return !buffer.empty() || done; });

            if (!buffer.empty()) {
                item = buffer.front();
                buffer.pop(); // Consume the item
                std::cout << "Consumer " << id << " consumed: " << item << std::endl;
            } 
            // Exit if production is done and buffer is empty
            if (done && buffer.empty()) {
                break; // Exit if production is done and buffer is empty
            }
        }
        // Notify one consumer after consuming
        cv.notify_one(); 
    }
}

int main() {
    std::thread prodThread(producer);
    std::thread consThread1(consumer, 1);
    std::thread consThread2(consumer, 2);

    prodThread.join();
    consThread1.join();
    consThread2.join();

    return 0; // Return success
}
