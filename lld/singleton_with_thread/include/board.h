#include <memory>
#include <mutex>

#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    Board() = default;  // Make constructor private
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(const Board&&) = delete;
    Board& operator=(const Board&&) = delete;
    
    static std::unique_ptr<Board> instance;
    static std::mutex instance_mutex;  // Add mutex for thread safety
    
    // Make std::make_unique a friend to allow object creation
    friend std::unique_ptr<Board> std::make_unique<Board>();
    
public:
    static std::unique_ptr<Board>& getInstance();
};

#endif