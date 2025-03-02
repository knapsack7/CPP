#include "TicTacToe.h"
#include <iostream>
#include <stdexcept>

TicTacToe::TicTacToe(int boardSize, GameMode mode) : board(boardSize), gameOver(false), winner(' ') {
    PlayerFactory factory;
    
    // Initialize players based on game mode
    switch (mode) {
        case GameMode::HUMAN_VS_HUMAN:
            player1 = factory.createHumanPlayer('X', board);
            player2 = factory.createHumanPlayer('O', board);
            break;
            
        case GameMode::HUMAN_VS_AI:
            player1 = factory.createHumanPlayer('X', board);
            player2 = factory.createAIPlayer('O', board);
            break;
            
        case GameMode::AI_VS_AI:
            player1 = factory.createAIPlayer('X', board);
            player2 = factory.createAIPlayer('O', board);
            break;
    }
    
    currentPlayer = player1.get();
}

void TicTacToe::startGame() {
    std::cout << "Game started!\n";
    board.printBoard();
    
    while (!gameOver) {
        std::cout << "Player " << currentPlayer->getSymbol() << "'s turn\n";
        
        // Get move from current player
        std::pair<int, int> move = currentPlayer->makeMove();
        
        try {
            makeMove(move.first, move.second);
            board.printBoard();
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
    
    board.makeMove(row, col, currentPlayer->getSymbol());
    
    // Check for win or draw
    if (board.checkWin(currentPlayer->getSymbol())) {
        gameOver = true;
        winner = currentPlayer->getSymbol();
    } else if (board.isFull()) {
        gameOver = true;
    } else {
        // Switch players
        currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
    }
}

