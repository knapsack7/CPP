#include "Board.h"

Board::Board() {
    reset();
}

bool Board::makeMove(int row, int col, char symbol) {
    if (!isValidMove(row, col)) {
        return false;
    }
    
    grid[row][col] = symbol;
    moveCount++;
    return true;
}

bool Board::isValidMove(int row, int col) const {
    // Check if position is within bounds
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    
    // Check if position is empty
    return grid[row][col] == ' ';
}

bool Board::isFull() const {
    return moveCount == BOARD_SIZE * BOARD_SIZE;
}

char Board::checkWinner() const {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            return grid[i][0];
        }
    }
    
    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            return grid[0][i];
        }
    }
    
    // Check diagonal (top-left to bottom-right)
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        return grid[0][0];
    }
    
    // Check diagonal (top-right to bottom-left)
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        return grid[0][2];
    }
    
    // No winner
    return '\0';
}

char Board::getValueAt(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return '\0';  // Return null character for invalid positions
    }
    return grid[row][col];
}

void Board::reset() {
    // Initialize grid with empty spaces
    grid.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        grid[i].resize(BOARD_SIZE, ' ');
    }
    moveCount = 0;
}

void Board::display() const {
    std::cout << "\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << grid[i][j];
            if (j < BOARD_SIZE - 1) {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        if (i < BOARD_SIZE - 1) {
            std::cout << "-----------\n";
        }
    }
    std::cout << "\n";
}

std::vector<std::pair<int, int>> Board::getAvailableMoves() const {
    std::vector<std::pair<int, int>> moves;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (grid[i][j] == ' ') {
                moves.push_back(std::make_pair(i, j));
            }
        }
    }
    
    return moves;
}

int Board::getMoveCount() const {
    return moveCount;
}

int Board::getSize() const {
    return BOARD_SIZE;
}

int Board::getCell(int i, int j) const{
    if (i < 0 || i >= BOARD_SIZE || j < 0 || j>= BOARD_SIZE){
        std::cout<<"Wrong idx\n";
        return -1;
    }
    return grid[i][j]; 
}