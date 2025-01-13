#include <array>
#include <cassert>
#include <future>
#include <iostream>

int main()
{
    std::atomic<char> counter = 0;

    auto future1 = std::async(std::launch::async, [&]() {
                                  counter++;
                              });
    auto future2 = std::async(std::launch::async, [&]() {
                                  return counter.load();
                              });
    future1.wait();
    std::cout << (int)future2.get();
    static_assert(counter.is_always_lock_free);
    assert(counter.is_lock_free());

    std::cout << "\n\n"
              << std::atomic<int>{}.is_lock_free()
              << std::atomic<long>{}.is_lock_free()
              << std::atomic<double>{}.is_lock_free()
              << "\n";

    std::cout << "\n"
              << std::atomic<int>{}.is_always_lock_free
              << std::atomic<long>{}.is_always_lock_free
              << std::atomic<double>{}.is_always_lock_free
              << "\n";
}
