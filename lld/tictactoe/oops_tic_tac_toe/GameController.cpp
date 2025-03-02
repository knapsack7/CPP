#include <unordered_map>
#include <memory>
#include <iostream>
#include "TicTacToe.h"

class GameController {
private:
    std::unordered_map<int, std::unique_ptr<TicTacToe>> games;
    static int gameIdCounter;

public:
    static GameController& getInstance() {
        static GameController instance;
        return instance;
    }

    int createGame(int boardSize, GameMode gameMode) {
        int gameId = gameIdCounter++;
        games[gameId] = std::make_unique<TicTacToe>(boardSize, gameMode);
        return gameId;
    }

    int startGame(int gameId){
        auto game = games.find(gameId);
        if (game != games.end()){
            game->second->startGame();
        } else {
            std::cout<<"Game Not Found\n";
        }
    }

    TicTacToe* getGame(int gameId) {
        auto it = games.find(gameId);
        if (it != games.end()) {
            return it->second.get();
        }
        return nullptr;
    }
};

// Initialize static variable
int GameController::gameIdCounter = 0;