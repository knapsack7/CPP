#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// Global mutex to protect access to the shared vector
std::mutex queueMutex;

// Shared resource: a vector to store log messages
std::vector<std::string> logMessages;

// Function to simulate logging messages
void workerFunction(int threadId) {
    // Simulate some work being done by this thread
    for (int i = 0; i < 5; ++i) {
        // Create a log message
        std::string logMessage = "Thread " + std::to_string(threadId) + " logged message " + std::to_string(i);

        // Lock the mutex to safely access the shared resource (logMessages)
        {
            // Create a lock_guard, which locks the mutex upon creation
            std::lock_guard<std::mutex> lock(queueMutex);
            // Critical section starts here: only this thread can access logMessages
            logMessages.push_back(logMessage); // Safely add the log message to the vector
            // Critical section ends here: lock_guard goes out of scope and automatically unlocks the mutex
        }

        // Simulate doing other work (not protected by the mutex)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Function to print all logged messages
void printLogs() {
    // Lock the mutex to read the shared resource safely
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        // Critical section starts here: only this thread can access logMessages
        std::cout << "Logged messages:" << std::endl;
        for (const auto& message : logMessages) {
            std::cout << message << std::endl; // Print each log message
        }
        // Critical section ends here: lock_guard goes out of scope and automatically unlocks the mutex
    }
}

int main() {
    const int numThreads = 3; // Number of threads to create
    std::vector<std::thread> threads; // Vector to hold thread objects

    // Create multiple threads that will log messages
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(workerFunction, i); // Start each thread with workerFunction
    }

    // Wait for all threads to finish execution
    for (auto& thread : threads) {
        thread.join(); // Join each thread to the main thread
    }

    // Print all logged messages
    printLogs();

    return 0; // Return success
}
