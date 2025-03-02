#include <iostream>
#include <memory>
#include "Game.h"
#include "PlayerFactory.h"

int main() {
    std::cout << "=== Welcome to Tic Tac Toe ===" << std::endl;
    
    // Create the game
    Game game;
    
    // Play the game
    game.play();
    
    std::cout << "\nThanks for playing Tic Tac Toe!" << std::endl;
    
    return 0;
}

