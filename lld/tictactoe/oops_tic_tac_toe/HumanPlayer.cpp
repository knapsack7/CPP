#include "HumanPlayer.h"
#include "Board.h"
#include <iostream>

/**
 * Constructor implementation
 * Note: We pass the parameters to the base class constructor in the correct order (name, marker)
 * even though our parameter order is (marker, name)
 */
HumanPlayer::HumanPlayer(const std::string& name, char marker)
    : Player(name, marker) {
    // Nothing else to initialize
}

/**
 * Destructor implementation
 */
HumanPlayer::~HumanPlayer() {
    // No dynamic memory to clean up
}

/**
 * Implementation of makeMove method
 * Gets input from the user and places marker on the board
 */
bool HumanPlayer::makeMove(Board& board) {
    int row, col;
    bool validMove = false;
    
    // Keep trying until we get a valid move
    while (!validMove) {
        std::cout << getName() << ", it's your turn (" << getMarker() << ")" << std::endl;
        std::cout << "Enter row (0-2): ";
        std::cin >> row;
        std::cout << "Enter column (0-2): ";
        std::cin >> col;
        
        // Check if input is valid
        if (std::cin.fail()) {
            std::cin.clear();  // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Skip bad input
            std::cout << "Invalid input. Please enter numbers." << std::endl;
            continue;
        }
        
        // Try to make the move
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            if (board.makeMove(row, col, getMarker())) {
                validMove = true;
            } else {
                std::cout << "That spot is already taken. Try again." << std::endl;
            }
        } else {
            std::cout << "Invalid position. Rows and columns must be between 0 and 2." << std::endl;
        }
    }
    
    return true;  // Move was successfully made
}

