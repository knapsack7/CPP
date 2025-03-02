#include <iostream>
#include "Board.cpp"
// Forward declaration of Board class
class Board;

// MoveStrategy Interface
class MoveStrategy {
public:
    virtual bool isValidMove(const Board& board, int x, int y) const = 0;
    virtual ~MoveStrategy() {} // Virtual destructor
};

// WinStrategy Interface
class WinStrategy {
public:
    virtual bool checkWin(const Board& board, char symbol) const = 0;
    virtual ~WinStrategy() {} // Virtual destructor
};

// Default Move Strategy Implementation
class DefaultMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(const Board& board, int x, int y) const override;
};

// Default Win Strategy Implementation
class DefaultWinStrategy : public WinStrategy {
public:
    bool checkWin(const Board& board, char symbol) const override;

private:
    bool checkRow(const Board& board, char symbol, int row) const;
    bool checkColumn(const Board& board, char symbol, int col) const;
    bool checkDiagonal(const Board& board, char symbol) const;
    bool checkAntiDiagonal(const Board& board, char symbol) const;
};

// Implementing DefaultMoveStrategy
bool DefaultMoveStrategy::isValidMove(const Board& board, int x, int y) const {
    return board.getCell(x, y) == ' '; // Assuming empty cell is ' '
}

// Implementing DefaultWinStrategy
bool DefaultWinStrategy::checkWin(const Board& board, char symbol) const {
    int size = board.getSize();
    
    // Check rows and columns
    for (int i = 0; i < size; ++i) {
        if (checkRow(board, symbol, i) || checkColumn(board, symbol, i)) {
            return true;
        }
    }
    
    // Check diagonals
    return checkDiagonal(board, symbol) || checkAntiDiagonal(board, symbol);
}

// Check if a row is filled with the same symbol
bool DefaultWinStrategy::checkRow(const Board& board, char symbol, int row) const {
    for (int i = 0; i < board.getSize(); ++i) {
        if (board.getCell(row, i) != symbol) {
            return false;
        }
    }
    return true;
}

// Check if a column is filled with the same symbol
bool DefaultWinStrategy::checkColumn(const Board& board, char symbol, int col) const {
    for (int i = 0; i < board.getSize(); ++i) {
        if (board.getCell(i, col) != symbol) {
            return false;
        }
    }
    return true;
}

// Check if the main diagonal is filled with the same symbol
bool DefaultWinStrategy::checkDiagonal(const Board& board, char symbol) const {
    for (int i = 0; i < board.getSize(); ++i) {
        if (board.getCell(i, i) != symbol) {
            return false;
        }
    }
    return true;
}

// Check if the anti-diagonal is filled with the same symbol
bool DefaultWinStrategy::checkAntiDiagonal(const Board& board, char symbol) const {
    int size = board.getSize();
    for (int i = 0; i < size; ++i) {
        if (board.getCell(i, size - i - 1) != symbol) {
            return false;
        }
    }
    return true;
}