#pragma once

#include <unordered_map>
#include <memory>
#include "TicTacToe.h"

class GameController {
private:
    std::unordered_map<int, std::unique_ptr<TicTacToe>> games;
    int nextGameId = 0;

public:
    GameController();
    
    // Creates a new game with the specified board size and game mode
    // Returns the game ID for future reference
    int createGame(int boardSize, GameMode gameMode);
    
    // Checks if a game with the given ID exists
    bool gameExists(int gameId);
    
    // Gets a pointer to the game with the specified ID
    // Returns nullptr if game doesn't exist
    TicTacToe* getGame(int gameId);
    
    // Starts a game with the given ID
    void startGame(int gameId);
    
    // Ends and removes a game with the given ID
    void endGame(int gameId);
};

