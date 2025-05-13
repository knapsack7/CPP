/*
Memory Ordering Types:
relaxed: No ordering constraints
acquire: Ensures all previous writes are visible
release: Makes all previous writes visible
acq_rel: Both acquire and release
seq_cst: Sequential consistency
*/
class MemoryOrdering {
private:
    std::atomic<int> x{0};
    std::atomic<int> y{0};

public:
    void write() {
        // Relaxed ordering - no synchronization
        x.store(1, std::memory_order_relaxed);
        // Release ordering - makes previous writes visible
        y.store(1, std::memory_order_release);
    }

    void read() {
        // Acquire ordering - ensures we see all previous writes
        while(y.load(std::memory_order_acquire) != 1);
        // Now x must be 1
        assert(x.load(std::memory_order_relaxed) == 1);
    }
};