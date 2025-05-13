#include <iostream>
#include <vector>
#include <limits>

// ✅ Board Class (Handles game board)
class Board {
public:
    Board() {
        grid = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    }

    void display() {
        std::cout << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << " " << grid[i][j] << " ";
                if (j < 2) std::cout << "|";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "---+---+---\n";
        }
        std::cout << "\n";
    }

    bool isFull() {
        for (const auto& row : grid)
            for (char cell : row)
                if (cell == ' ') return false;
        return true;
    }

    bool placeMarker(int row, int col, char marker) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ')
            return false;
        grid[row][col] = marker;
        return true;
    }

    char checkWinner() {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ')
                return grid[i][0];
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ')
                return grid[0][i];
        }
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ')
            return grid[0][0];
        if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ')
            return grid[0][2];
        return ' ';
    }

    bool isCellEmpty(int row, int col) {
        return grid[row][col] == ' ';
    }

private:
    std::vector<std::vector<char>> grid;
};

// 📌 IPlayer Interface
class IPlayer {
public:
    virtual std::pair<int, int> getMove(Board& board) = 0;
    virtual ~IPlayer() = default;
};

// 📌 HumanPlayer (Takes user input)
class HumanPlayer : public IPlayer {
public:
    HumanPlayer(char marker) : marker(marker) {}

    std::pair<int, int> getMove(Board& board) override {
        int row, col;
        while (true) {
            std::cout << "Enter row and column (0-2) for marker " << marker << ": ";
            std::cin >> row >> col;
            if (std::cin.fail() || row < 0 || row >= 3 || col < 0 || col >= 3) {
                std::cout << "Invalid input! Try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (!board.isCellEmpty(row, col)) {
                std::cout << "Cell occupied! Choose another spot.\n";
                continue;
            }
            return {row, col};
        }
    }

private:
    char marker;
};

// 📌 AIPlayer (Picks first empty cell)
class AIPlayer : public IPlayer {
public:
    AIPlayer(char marker) : marker(marker) {}

    std::pair<int, int> getMove(Board& board) override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isCellEmpty(i, j)) {
                    return {i, j};
                }
            }
        }
        return {0, 0}; // Fallback (should never happen)
    }

private:
    char marker;
};

// 📌 TicTacToeGame Class
class TicTacToeGame {
public:
    TicTacToeGame(IPlayer* p1, IPlayer* p2) : player1(p1), player2(p2), currentPlayer(p1), currentMarker('X') {}

    void play() {
        Board board;
        while (!board.isFull()) {
            board.display();
            std::pair<int, int> move;
            do {
                move = currentPlayer->getMove(board);
            } while (!board.placeMarker(move.first, move.second, currentMarker));

            char winner = board.checkWinner();
            if (winner != ' ') {
                board.display();
                std::cout << "Player " << winner << " wins!\n";
                return;
            }

            switchPlayer();
        }
        board.display();
        std::cout << "It's a draw!\n";
    }

private:
    IPlayer* player1;
    IPlayer* player2;
    IPlayer* currentPlayer;
    char currentMarker;

    void switchPlayer() {
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
        currentMarker = (currentMarker == 'X') ? 'O' : 'X';
    }
};

// 📌 Main function to run the game
int main() {
    HumanPlayer p1('X');
    AIPlayer p2('O');

    TicTacToeGame game(&p1, &p2);
    game.play();

    return 0;
}
