#pragma once

#include "Board.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <memory>

/**
 * Game class - manages the tic-tac-toe game logic
 * Handles player turns, game state, and win conditions
 */
class Game {
private:
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<Player>> players;
    int currentPlayerIndex;
    bool gameOver;

public:
    /**
     * Constructor - initializes a new game
     */
    Game();
    
    /**
     * Destructor - no longer needs to manually free memory due to shared_ptr usage
     */
    ~Game();
    /**
     * Initialize the game with players
     */
    void initialize();
    
    /**
     * Play the complete game until there's a winner or draw
     */
    void play();
    
    /**
     * Display the current state of the board
     */
    void displayBoard() const;
    
    /**
     * Check if the current player has won the game
     * @return true if the current player has won, false otherwise
     */
    bool checkWin() const;
    
    /**
     * Check if the game is a draw
     * @return true if the game is a draw, false otherwise
     */
    bool checkDraw() const;
};

