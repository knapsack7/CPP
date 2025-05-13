#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Move Strategy Interface
class MoveStrategy {
public:
    virtual pair<int, int> getMove(vector<vector<char>>& board, char player) = 0;
    virtual ~MoveStrategy() {}
};

// Human Player Move Strategy
class HumanMoveStrategy : public MoveStrategy {
public:
    pair<int, int> getMove(vector<vector<char>>& board, char player) override {
        int row, col;
        while (true) {
            cout << "Enter your move (row and col): ";
            cin >> row >> col;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                return {row, col};
            }
            cout << "Invalid move. Try again." << endl;
        }
    }
};

// Random AI Move Strategy
class RandomMoveStrategy : public MoveStrategy {
public:
    pair<int, int> getMove(vector<vector<char>>& board, char player) override {
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    emptyCells.push_back({i, j});
                }
            }
        }
        if (!emptyCells.empty()) {
            return emptyCells[rand() % emptyCells.size()];
        }
        return {-1, -1}; // No valid moves
    }
};

// Minimax AI Move Strategy (Optimal)
class MinimaxMoveStrategy : public MoveStrategy {
private:
    char aiPlayer, humanPlayer;

    // Check for game result
    int evaluate(vector<vector<char>>& board) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                if (board[i][0] == aiPlayer) return 10;
                if (board[i][0] == humanPlayer) return -10;
            }
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                if (board[0][i] == aiPlayer) return 10;
                if (board[0][i] == humanPlayer) return -10;
            }
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == aiPlayer) return 10;
            if (board[0][0] == humanPlayer) return -10;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == aiPlayer) return 10;
            if (board[0][2] == humanPlayer) return -10;
        }
        return 0;
    }

    // Check if board is full
    bool isMovesLeft(vector<vector<char>>& board) {
        for (auto& row : board)
            for (char cell : row)
                if (cell == ' ') return true;
        return false;
    }

    // Minimax Algorithm
    int minimax(vector<vector<char>>& board, int depth, bool isMax) {
        int score = evaluate(board);

        if (score == 10) return score - depth; // AI wins
        if (score == -10) return score + depth; // Human wins
        if (!isMovesLeft(board)) return 0; // Draw

        if (isMax) {
            int best = numeric_limits<int>::min();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = aiPlayer;
                        best = max(best, minimax(board, depth + 1, false));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = humanPlayer;
                        best = min(best, minimax(board, depth + 1, true));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
    }

public:
    MinimaxMoveStrategy(char ai, char human) : aiPlayer(ai), humanPlayer(human) {}

    pair<int, int> getMove(vector<vector<char>>& board, char player) override {
        int bestVal = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = aiPlayer;
                    int moveVal = minimax(board, 0, false);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }
};

// Player Class
class Player {
private:
    char symbol;
    MoveStrategy* strategy;
public:
    Player(char sym, MoveStrategy* strat) : symbol(sym), strategy(strat) {}

    pair<int, int> makeMove(vector<vector<char>>& board) {
        return strategy->getMove(board, symbol);
    }

    char getSymbol() const { return symbol; }
};

// Tic Tac Toe Game
class TicTacToe {
private:
    vector<vector<char>> board;
    Player* playerX;
    Player* playerO;

    void printBoard() {
        cout << "Current Board:\n";
        for (auto& row : board) {
            for (char cell : row) {
                cout << (cell == ' ' ? '-' : cell) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool isWin(char symbol) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
        }
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
        return false;
    }

    bool isDraw() {
        for (auto& row : board)
            for (char cell : row)
                if (cell == ' ') return false;
        return true;
    }

public:
    TicTacToe(Player* pX, Player* pO) : playerX(pX), playerO(pO), board(3, vector<char>(3, ' ')) {}

    void playGame() {
        Player* currentPlayer = playerX;
        printBoard();

        while (true) {
            cout << "Player " << currentPlayer->getSymbol() << "'s turn.\n";
            pair<int, int> move = currentPlayer->makeMove(board);

            board[move.first][move.second] = currentPlayer->getSymbol();
            printBoard();

            if (isWin(currentPlayer->getSymbol())) {
                cout << "Player " << currentPlayer->getSymbol() << " wins!\n";
                return;
            }

            if (isDraw()) {
                cout << "It's a draw!\n";
                return;
            }

            currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
        }
    }
};

// Main function
int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Create strategies for players
    HumanMoveStrategy* humanStrategy = new HumanMoveStrategy();
    MinimaxMoveStrategy* aiStrategy = new MinimaxMoveStrategy('O', 'X');
    
    // Create players
    Player* humanPlayer = new Player('X', humanStrategy);
    Player* aiPlayer = new Player('O', aiStrategy);
    
    // Initialize and start the game
    cout << "Starting Tic-Tac-Toe game: Human (X) vs AI (O)" << endl;
    TicTacToe game(humanPlayer, aiPlayer);
    game.playGame();
    
    // Clean up memory
    delete humanPlayer;
    delete aiPlayer;
    delete humanStrategy;
    delete aiStrategy;
    
    return 0;
}
