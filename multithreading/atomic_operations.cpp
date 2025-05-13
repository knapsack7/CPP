#include <atomic>

class AtomicCounter {
private:
    std::atomic<int> count{0};  // Atomic integer

public:
    void increment() {
        // Atomic operation - no need for mutex
        count.fetch_add(1, std::memory_order_relaxed);
    }

    int get() const {
        return count.load(std::memory_order_relaxed);
    }
};

/*
  std::memory_order_relaxed  // No ordering constraints
  std::memory_order_acquire  // Read operation
  std::memory_order_release  // Write operation
  std::memory_order_acq_rel  // Both read and write
  std::memory_order_seq_cst  // Sequential consistency
*/

/*
  std::atomic<T>  // T can be any trivially copyable type
  std::atomic_flag  // Boolean flag, always lock-free
*/

/*
Use cases:
Simple counters
Flags
Lock-free algorithms
Performance-critical sections
*/