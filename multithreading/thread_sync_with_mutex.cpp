#include <mutex>
#include <condition_variable>

/*
    Condition variables:
    Used for thread signaling
    wait(): Thread waits until condition is met
    notify_one(): Wake up one waiting thread
    notify_all(): Wake up all waiting threads
*/


/*
  std::lock_guard    // RAII wrapper, locks on construction, unlocks on destruction
  std::unique_lock   // More flexible, can be locked/unlocked multiple times
  std::scoped_lock   // C++17, can lock multiple mutexes atomically
*/

/*
  std::mutex              // Basic mutex
  std::recursive_mutex    // Can be locked multiple times by same thread
  std::timed_mutex        // Can try to lock with timeout
  std::recursive_timed_mutex  // Both recursive and timed
*/


class ThreadSafeCounter {
private:
    std::mutex mtx;  // Mutex for protecting shared data
    int count = 0;   // Shared data
    std::condition_variable cv;  // For thread signaling

public:
    void increment() {
        // RAII style locking - automatically unlocks when scope ends
        std::lock_guard<std::mutex> lock(mtx);
        count++;
        // Notify one waiting thread
        cv.notify_one();
    }

    void waitForCount(int target) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until condition is met
        cv.wait(lock, [this, target]() { 
            return count >= target; 
        });
    }
};