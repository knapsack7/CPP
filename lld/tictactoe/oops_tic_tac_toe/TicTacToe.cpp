#include "TicTacToe.h"
#include <iostream>
#include <stdexcept>

TicTacToe::TicTacToe(int boardSize, GameMode mode) : board(), gameOver(false), winner(' ') {
    PlayerFactory factory;
    
    // Initialize players based on game mode
    switch (mode) {
        case GameMode::HUMAN_VS_HUMAN:
            player1 = factory.createHumanPlayer("Player X", 'X');
            player2 = factory.createHumanPlayer("Player O", 'O');
            break;
            
        case GameMode::HUMAN_VS_AI:
            player1 = factory.createHumanPlayer("Player X", 'X');
            player2 = factory.createAIPlayer("Computer", 'O');
            break;
            
        case GameMode::AI_VS_AI:
            player1 = factory.createAIPlayer("Computer 1", 'X');
            player2 = factory.createAIPlayer("Computer 2", 'O');
            break;
    }
    
    currentPlayer = player1.get();
}

void TicTacToe::startGame() {
    std::cout << "Game started!\n";
    board.display();
    
    while (!gameOver) {
        std::cout << "Player " << currentPlayer->getMarker() << "'s turn\n";
        
        // Get move from current player
        try {
            bool moveMade = currentPlayer->makeMove(board);
            if (!moveMade) {
                std::cout << "Move failed. Try again.\n";
                continue;
            }
            board.display();
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            continue;
        }
    }
    
    if (winner != ' ') {
        std::cout << "Player " << winner << " wins!\n";
    } else {
        std::cout << "It's a draw!\n";
    }
}

char TicTacToe::getWinner() const {
    return winner;
}

bool TicTacToe::isGameOver() const {
    return gameOver;
}

void TicTacToe::makeMove(int row, int col) {
    if (gameOver) {
        throw std::runtime_error("Game is already over");
    }
    
    if (!board.isValidMove(row, col)) {
        throw std::invalid_argument("Invalid move");
    }
    
    board.makeMove(row, col, currentPlayer->getMarker());
    
    // Check for win or draw
    char winner_marker = board.checkWinner();
    if (winner_marker == currentPlayer->getMarker()) {
        gameOver = true;
        winner = currentPlayer->getMarker();
    } else if (board.isFull()) {
        gameOver = true;
    } else {
        // Switch players
        currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
    }
}

