#include <iostream>
#include <vector>
#include "Board.cpp"

class GameEngine {
public:
    virtual void playTurn(int x, int y) = 0;
    virtual bool isGameOver() = 0;
    virtual ~GameEngine() = default;
};

class UIHandler {
public:
    virtual std::pair<int, int> getMove() = 0;
    virtual void displayBoard(const Board& board) = 0;
    virtual ~UIHandler() = default;
};

class ConsoleUIHandler : public UIHandler {
public:
    std::pair<int, int> getMove() override {
        int x, y;
        std::cout << "Enter row: ";
        std::cin >> x;
        std::cout << "Enter column: ";
        std::cin >> y;
        return {x, y};
    }

    void displayBoard(const Board& board) override {
        for (int i = 0; i < board.getSize(); ++i) {
            for (int j = 0; j < board.getSize(); ++j) {
                std::cout << board.getCell(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};