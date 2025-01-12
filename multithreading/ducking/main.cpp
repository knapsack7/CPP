#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> isDucking(false);

void navigationSystem() {
    while (true) {
        // Simulate a navigation announcement
        std::this_thread::sleep_for(std::chrono::seconds(5));
        isDucking = true; // Signal to duck
        std::cout << "Navigation: Turn right in 100 meters!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        isDucking = false; // Restore normal volume
    }
}

void musicSystem() {
    while (true) {
        if (isDucking) {
            std::cout << "Music volume: Low" << std::endl;
        } else {
            std::cout << "Music volume: Normal" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread navThread(navigationSystem);
    std::thread musicThread(musicSystem);

    navThread.join();
    musicThread.join();
    return 0;
}
