/*
Deadlock Prevention Techniques:
Always lock mutexes in the same order
Use std::lock for multiple mutexes
Use timeouts with try_lock
Use RAII lock guards
*/
class DeadlockPrevention {
private:
    std::mutex mtx1, mtx2;

public:
    void safeOperation() {
        // Lock both mutexes atomically
        std::lock(mtx1, mtx2);
        
        // Adopt the locks (they're already locked)
        std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
        
        // Do work
    }
};