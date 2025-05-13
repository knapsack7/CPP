#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "PlayerFactory.h"
#include <iostream>
#include <limits>

Game::Game() : currentPlayerIndex(0), gameOver(false) {
    board = std::make_shared<Board>();
}

Game::~Game() {
    // No need to manually delete shared_ptr objects
    players.clear();
}

void Game::initialize() {
    // Create two players using PlayerFactory based on user input
    int choice;
    
    std::cout << "Select game mode:" << std::endl;
    std::cout << "1. Human vs Human" << std::endl;
    std::cout << "2. Human vs AI" << std::endl;
    std::cout << "3. AI vs AI" << std::endl;
    std::cout << "Enter your choice (1-3): ";
    
    while (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter 1, 2, or 3: ";
    }
    
    switch (choice) {
        case 1: // Human vs Human
            players.push_back(PlayerFactory::createHumanPlayer("Player X", 'X'));
            players.push_back(PlayerFactory::createHumanPlayer("Player O", 'O'));
            break;
        case 2: // Human vs AI
            players.push_back(PlayerFactory::createHumanPlayer("Player X", 'X'));
            players.push_back(PlayerFactory::createAIPlayer("AI O", 'O'));
            break;
        case 3: // AI vs AI
            players.push_back(PlayerFactory::createAIPlayer("AI X", 'X'));
            players.push_back(PlayerFactory::createAIPlayer("AI O", 'O'));
            break;
    }
    
    // Reset the game state
    currentPlayerIndex = 0;
    gameOver = false;
}

void Game::play() {
    initialize();
    
    // Main game loop
    while (!gameOver) {
        // Display the current board state
        displayBoard();
        
        // Get the current player
        std::shared_ptr<Player> currentPlayer = players[currentPlayerIndex];
        std::cout << "\n" << currentPlayer->getName() << "'s turn (" << currentPlayer->getMarker() << ")" << std::endl;
        
        // Current player makes a move
        currentPlayer->makeMove(*board);
        
        // Check if the game is over
        if (checkWin()) {
            displayBoard();
            std::cout << "\nCongratulations! " << currentPlayer->getName() << " wins!" << std::endl;
            gameOver = true;
        } 
        else if (checkDraw()) {
            displayBoard();
            std::cout << "\nThe game is a draw!" << std::endl;
            gameOver = true;
        }
        
        // Switch to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
    
    // Ask to play again
    char playAgain;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> playAgain;
    
    if (playAgain == 'y' || playAgain == 'Y') {
        // Reset the board
        board = std::make_shared<Board>();
        
        // Clear players
        players.clear();
        
        // Start a new game
        gameOver = false;
        play();
    }
}

void Game::displayBoard() const {
    std::cout << "\n";
    board->display();
    std::cout << "\n";
}

bool Game::checkWin() const {
    char marker = players[currentPlayerIndex]->getMarker();
    
    // Check for a winner using Board's checkWinner method
    char winner = board->checkWinner();
    return winner == marker;
}

bool Game::checkDraw() const {
    // Game is a draw if the board is full and there's no winner
    return board->isFull();
}
