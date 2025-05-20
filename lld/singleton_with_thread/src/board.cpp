#include "../include/board.h"
#include <iostream>
#include <stdexcept>

std::unique_ptr<Board> Board::instance = nullptr;
std::mutex Board::instance_mutex;

std::unique_ptr<Board>& Board::getInstance() {
    std::lock_guard<std::mutex> lock(instance_mutex);  // Lock the mutex
    if (instance == nullptr) {
        std::cout << "Creating new instance of Board" << std::endl;
        instance = std::make_unique<Board>();
    } else {
        throw std::runtime_error("Attempt to create second instance of Board");
    }
    return instance;
}