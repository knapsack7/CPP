#pragma once

#include <vector>
#include <iostream>

// Forward declaration of Player class
class Player;

/**
 * Board class - represents the tic-tac-toe game board
 */
class Board {
private:
    static const int BOARD_SIZE = 3;
    std::vector<std::vector<char>> grid;
    int moveCount;

public:
    /**
     * Constructor - initializes an empty board
     */
    Board();

    /**
     * Make a move on the board
     * @param row Row index (0-2)
     * @param col Column index (0-2)
     * @param symbol Symbol to place ('X' or 'O')
     * @return true if move was successful, false if invalid
     */
    bool makeMove(int row, int col, char symbol);

    /**
     * Check if a move is valid
     * @param row Row index (0-2)
     * @param col Column index (0-2)
     * @return true if the move is valid, false otherwise
     */
    bool isValidMove(int row, int col) const;

    /**
     * Check if the board is full
     * @return true if the board is full, false otherwise
     */
    bool isFull() const;

    /**
     * Check if there's a winner
     * @return 'X', 'O' if there's a winner, '\0' otherwise
     */
    char checkWinner() const;

    /**
     * Get the value at a specific position
     * @param row Row index (0-2)
     * @param col Column index (0-2)
     * @return The character at the specified position
     */
    char getValueAt(int row, int col) const;

    /**
     * Reset the board to its initial state
     */
    void reset();

    /**
     * Display the current state of the board
     */
    void display() const;

    /**
     * Get all available moves on the board
     * @return Vector of pairs representing available positions (row, col)
     */
    std::vector<std::pair<int, int>> getAvailableMoves() const;

    /**
     * Get the current move count
     * @return The number of moves made
     */
    int getMoveCount() const;
};

