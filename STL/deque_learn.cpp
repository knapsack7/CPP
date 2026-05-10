/*
 * Learning std::deque in C++
 *
 * Topics covered:
 * 1. What is deque and basic operations
 * 2. How index-based access (operator[]) is provided
 * 3. How indexing is maintained when deque grows or shrinks
 *
 * Compile: g++ -std=c++17 -Wall -o deque_learn deque_learn.cpp
 */

#include <deque>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// =============================================================================
// PART 1: What is std::deque?
// =============================================================================
//
// std::deque = "double-ended queue"
// - Random access by index: d[i] in O(1) (like vector)
// - Push/pop at BOTH front and back: O(1) amortized (unlike vector, which is
//   O(1) at back only; front push/pop on vector is O(n) due to shifting)
// - Implemented as a sequence of fixed-size "chunks" (buffers), not one
//   contiguous block like vector. So it's often called "chunked" or
//   "segmented" storage.
//
// Internal model (conceptual; exact layout is implementation-defined):
//
//   Map (array of pointers):  [ptr0][ptr1][ptr2][ptr3]...
//                                    \    |    /
//   Chunks (fixed-size arrays):      [a..][b..][c..]
//                                    ^         ^
//                              front chunk  back chunk
//
// Elements are stored in chunks. The "map" holds pointers to those chunks.
// First element might not be at index 0 of the first chunk (if we've popped
// from front); last element might not fill the last chunk. So the implementation
// keeps a "start" and "end" (chunk + offset) to know where the logical [0]
// and [size()-1] live.

void part1_basics() {
    std::cout << "\n=== Part 1: deque basics ===\n";

    std::deque<int> d = {10, 20, 30, 40, 50};

    // Index-based access: same syntax as vector
    std::cout << "d[0] = " << d[0] << ", d[2] = " << d[2] << ", d[4] = " << d[4] << "\n";

    d.push_front(5);   // O(1) amortized at front (vector would be O(n))
    d.push_back(60);  // O(1) amortized at back

    std::cout << "After push_front(5), push_back(60): ";
    for (size_t i = 0; i < d.size(); ++i)
        std::cout << d[i] << " ";
    std::cout << "\n";

    d.pop_front();
    d.pop_back();
    std::cout << "After pop_front(), pop_back(): ";
    for (size_t i = 0; i < d.size(); ++i)
        std::cout << d[i] << " ";
    std::cout << "\n";
}

// =============================================================================
// PART 2: How is index-based support provided?
// =============================================================================
//
// operator[](size_type i) must return the element at "logical" index i in O(1).
//
// Implementation strategy (typical):
// - Deque has a "map": an array of pointers, each pointing to a chunk (fixed-size
//   array of T). Chunk size is often 512 bytes / sizeof(T) or similar.
// - It stores:
//   - start_chunk, start_offset  -> where element 0 lives
//   - end_chunk, end_offset      -> one past the last element
//
// To compute the location of index i:
//   logical_index = start_offset + i   (in "element units" from start of first chunk)
//   chunk_index   = logical_index / chunk_size
//   offset_in_chunk = logical_index % chunk_size
//
// So:  element at i  =  map[start_chunk + chunk_index][offset_in_chunk]
//
// This is O(1): two integer ops (div/mod or equivalent) and two pointer dereferences.
// No iteration, no reallocation. Hence deque supports random access by index.

void part2_index_access() {
    std::cout << "\n=== Part 2: Index-based access ===\n";

    std::deque<std::string> d;
    d.push_back("zero");
    d.push_back("one");
    d.push_back("two");
    d.push_back("three");

    // operator[] and at() both give index-based access.
    // at() does bounds checking and throws std::out_of_range if i >= size().
    std::cout << "d[0] = " << d[0] << ", d[3] = " << d[3] << "\n";
    std::cout << "d.at(1) = " << d.at(1) << "\n";

    // Front and back are just d[0] and d[size()-1]; deque stores them so these
    // are O(1) without scanning.
    std::cout << "d.front() = " << d.front() << ", d.back() = " << d.back() << "\n";
}

// =============================================================================
// PART 3: How is indexing maintained when deque grows or shrinks?
// =============================================================================
//
// Key idea: "Index" is always a logical position 0, 1, 2, ..., size()-1.
// The implementation maps that logical index to (chunk, offset) as above.
// When we grow or shrink, we only add/remove chunks or change start/end;
// we do NOT move existing elements to "re-index" them.
//
// When deque GROWS:
// - push_back: if current back chunk has room, put element there and advance
//   end_offset. If no room, allocate a NEW chunk, add its pointer to the map
//   (possibly growing the map itself), put element in new chunk. Existing
//   elements stay where they are → their indices (0, 1, ...) unchanged.
// - push_front: same from the other side; may need a new chunk at the front.
//   If the map has no slot at the front, implementation may either:
//   (a) reallocate the map and shift pointers so there is room at front, or
//   (b) use a circular map. Existing elements are never moved; only the
//   "start_chunk/start_offset" (or equivalent) change. So d[0] still refers
//   to the same logical element; the mapping (0 -> chunk,offset) is updated
//   by the start position, not by moving data.
//
// When deque SINKS (pop_back, pop_front):
// - We decrement size and adjust end (or start). If a chunk becomes empty,
//   it can be deallocated and removed from the map. Again, no element moves:
//   what was at index 1 is still at index 1; we just have a smaller size(),
//   so index 1 still refers to the same element. Indices are logical.
//
// Summary:
// - Indices are logical (0 to size()-1). They are not "physical" positions
//   in one array. The implementation maintains a stable mapping from
//   logical index -> (chunk, offset). When we grow/shrink, we only change
//   size and possibly the set of chunks; the mapping formula (start + i ->
//   chunk + offset) keeps indices consistent without moving existing elements.

void part3_grow_shrink_indexing() {
    std::cout << "\n=== Part 3: Indexing when growing/shrinking ===\n";

    std::deque<int> d = {100, 200, 300};
    std::cout << "Initial: d[0]=" << d[0] << " d[1]=" << d[1] << " d[2]=" << d[2] << "\n";

    // Grow from back: new elements get new indices; old indices unchanged
    d.push_back(400);
    d.push_back(500);
    std::cout << "After push_back(400), push_back(500): d[0]=" << d[0] << " d[3]=" << d[3] << " d[4]=" << d[4] << "\n";

    // Grow from front: logical index 0 shifts to the new element; old "0" becomes 1, etc.
    // So the SAME logical index still designates the SAME element after push_front.
    d.push_front(50);
    std::cout << "After push_front(50): d[0]=" << d[0] << " d[1]=" << d[1] << " (old d[0] is now d[1])\n";

    // Shrink from front: remove d[0], so old d[1] becomes new d[0]; indices stay logical
    d.pop_front();
    std::cout << "After pop_front(): d[0]=" << d[0] << " (was 100 at index 1 before)\n";

    d.pop_back();
    std::cout << "After pop_back(): back is now d[" << (d.size()-1) << "] = " << d.back() << "\n";
}

// =============================================================================
// Bonus: Iterator / reference stability
// =============================================================================
//
// Unlike vector: inserting or erasing at the front or middle of a vector
// invalidates iterators/references. In deque, push/pop at front or back
// does NOT invalidate references to other elements (only to the element
// removed). Iterators may be invalidated when the deque grows (map realloc),
// but references to elements that still exist remain valid. This is because
// elements are not moved to new memory when we grow/shrink from the ends.

void part4_reference_stability() {
    std::cout << "\n=== Part 4: Reference stability (bonus) ===\n";

    std::deque<int> d = {1, 2, 3, 4, 5};
    const int& ref = d[2];  // reference to element at index 2 (value 3)

    std::cout << "ref (to d[2]) = " << ref << "\n";
    d.push_front(0);
    d.push_back(6);
    // ref still valid and still 3 (same element, now still at some index)
    std::cout << "After push_front(0), push_back(6): ref = " << ref << " (still valid)\n";
    std::cout << "Element 3 is now at index " << 3 << ": d[3] = " << d[3] << "\n";
}

// =============================================================================
// PART 5: Multi-threaded access – avoiding out-of-bounds and panic
// =============================================================================
//
// std::deque is NOT thread-safe. Concurrent reads/writes without synchronization
// are data races → undefined behavior (crashes, corruption, no guarantees).
//
// Best practices:
//
// 1. Always protect the deque with a mutex when any thread may read or modify it.
//    Lock around the entire logical operation (e.g. "check size + access element"),
//    not just the single call. Otherwise:
//    - Thread A: size() returns 5
//    - Thread B: pop_back() → size is now 4
//    - Thread A: d[4] or d.at(4) → out-of-bounds (UB with [], exception with at()).
//
// 2. at() vs operator[] when sharing the deque:
//
//    - operator[]: NO bounds checking. If index >= size(), undefined behavior
//      (anything can happen: crash, wrong value, no error). Hard to debug.
//
//    - at(index): Bounds checking. If index >= size(), throws std::out_of_range.
//      So you get a well-defined failure and can catch it instead of undefined
//      behavior. In multi-threaded code, at() is generally PREFERRED when the
//      index might ever be invalid (e.g. index came from another thread or from
//      a stale size()). It does NOT make the deque thread-safe; it only makes
//      invalid access fail in a defined way.
//
// 3. Safe pattern: hold the lock for the whole "read size / validate index /
//    access" sequence. Prefer at() inside the lock so that any bug (wrong index)
//    yields an exception instead of UB. Optionally catch std::out_of_range and
//    handle (retry, return default, log, etc.).
//

// Example: shared deque guarded by a mutex; safe access by index using at()
class ThreadSafeDeque {
public:
    void push_back(int x) {
        std::lock_guard<std::mutex> lock(mtx_);
        dq_.push_back(x);
    }

    void push_front(int x) {
        std::lock_guard<std::mutex> lock(mtx_);
        dq_.push_front(x);
    }

    // Prefer at() so out-of-bounds throws instead of UB. Caller can catch.
    int at(size_t index) const {
        std::lock_guard<std::mutex> lock(mtx_);
        return dq_.at(index);  // throws std::out_of_range if index >= size()
    }

    // Optional: try_access returns false if index invalid (no exception).
    bool try_get(size_t index, int& out) const {
        std::lock_guard<std::mutex> lock(mtx_);
        if (index >= dq_.size()) return false;
        out = dq_.at(index);  // safe: we just checked; at() for consistency
        return true;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return dq_.size();
    }

private:
    mutable std::mutex mtx_;
    std::deque<int> dq_;
};

void part5_multithreaded_safe_access() {
    std::cout << "\n=== Part 5: Multi-threaded – safe indexing (at vs []) ===\n";

    ThreadSafeDeque safe;

    // Writer threads
    std::thread t1([&]() { for (int i = 0; i < 5; ++i) safe.push_back(i); });
    std::thread t2([&]() { for (int i = 10; i < 15; ++i) safe.push_front(i); });
    t1.join();
    t2.join();

    size_t n = safe.size();
    std::cout << "After two threads pushing: size = " << n << "\n";

    // Safe read: use at() so invalid index throws instead of UB.
    try {
        std::cout << "safe.at(0) = " << safe.at(0) << ", safe.at(" << (n - 1) << ") = " << safe.at(n - 1) << "\n";
        // This would throw; we catch instead of panic/UB.
        int x = safe.at(n + 100);
        (void)x;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught out_of_range as expected: " << e.what() << "\n";
    }

    // No-exception style: try_get for optional safe access.
    int val = -1;
    if (safe.try_get(0, val))
        std::cout << "try_get(0) -> " << val << "\n";
    if (!safe.try_get(n + 100, val))
        std::cout << "try_get(out_of_bounds) -> false, no panic\n";
}

int main() {
    std::cout << "Learning std::deque: index-based access and grow/shrink behavior\n";

    part1_basics();
    part2_index_access();
    part3_grow_shrink_indexing();
    part4_reference_stability();
    part5_multithreaded_safe_access();

    std::cout << "\nDone.\n";
    return 0;
}
