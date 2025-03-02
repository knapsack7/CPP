#pragma once

#include <memory>
#include <utility> // for std::pair
#include <stdexcept> // for exceptions
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "PlayerFactory.h"

// GameMode enum to specify different game modes
enum class GameMode {
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI,
    AI_VS_AI
};

// TicTacToe class to manage a single game instance
class TicTacToe {
private:
    Board board;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer;
    bool gameOver;
    char winner;

public:
    // Constructor that initializes a new game with specified board size and game mode
    TicTacToe(int boardSize, GameMode mode);
    
    // Starts and runs the game until completion
    void startGame();
    
    // Returns the winner's symbol (' ' if no winner)
    char getWinner() const;
    
    // Returns true if the game has ended
    bool isGameOver() const;
    
    // Makes a move at the specified position
    // Throws an exception for invalid moves
    void makeMove(int row, int col);
};

