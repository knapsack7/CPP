#include <shared_mutex>


/*
    Key Concepts:
    shared_mutex: Allows multiple readers but only one writer
    shared_lock: For read operations
    unique_lock: For write operations
    Use cases:
    When reads are more frequent than writes
    When reads can happen concurrently
    When writes need exclusive access

*/


class ReadWriteLock {
private:
    std::shared_mutex mtx;  // Allows multiple readers
    int data = 0;

public:
    // Multiple readers can access simultaneously
    int read() {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return data;
    }

    // Only one writer at a time
    void write(int value) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        data = value;
    }
};