#include "AIPlayer.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

AIPlayer::AIPlayer(const std::string& name, char marker) : Player(name, marker) {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

AIPlayer::~AIPlayer() {
    // Nothing to clean up
}

bool AIPlayer::makeMove(Board& board) {
    std::cout << getName() << " is thinking..." << std::endl;
    
    // Find all available (empty) cells
    std::vector<std::pair<int, int>> emptyCells;
    
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board.isValidMove(row, col)) {
                emptyCells.push_back(std::make_pair(row, col));
            }
        }
    }
    
    // If no empty cells remain, return false
    if (emptyCells.empty()) {
        return false;
    }
    
    // Choose a random empty cell
    int randomIndex = std::rand() % emptyCells.size();
    int row = emptyCells[randomIndex].first;
    int col = emptyCells[randomIndex].second;
    
    // Make the move
    std::cout << getName() << " places " << getMarker() << " at position (" 
              << row + 1 << "," << col + 1 << ")" << std::endl;
              
    return board.makeMove(row, col, getMarker());
}
