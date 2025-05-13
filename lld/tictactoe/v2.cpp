#include<iostream>
#include<string>

using namespace std;

//Enum for Cell States
enum class CellState {EMPTY, X, O};

//Player Class
class Player{
public:
    string name;
    CellState symbol;
    // Constructor
    Player(string name, CellState symbol) : name(name), symbol(symbol){}
};


class Board {
    vector<vector<CellState>> grid;
    int size;
public:
    Board(int n) : size(n), grid(n, vector<CellState>(n, CellState::EMPTY)) {}
    bool makeMove(int row, int col, CellState symbol) {
        if (row < 0 || row >= size || col < 0 || col >= size || grid[row][col] != CellState::EMPTY) {
            return false; // Invalid move
        }
        grid[row][col] = symbol;
        return true;
    }
    bool checkWin(CellState symbol) {
        // Check rows & columns
        for (int i = 0; i < size; i++) {
            if (checkRow(i, symbol) || checkColumn(i, symbol)) return true;
        }
        // Check diagonals
        return checkDiagonal(symbol);
    }
    
    bool isFull() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == CellState::EMPTY) return false;
            }
        }
        return true;
    }
    
    void printBoard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << (grid[i][j] == CellState::EMPTY ? "." : (grid[i][j] == CellState::X ? "X" : "O")) << " ";
            }
            cout << endl;
        }
    }
    
    private:
    bool checkRow(int row, CellState symbol) {
        for (int j = 0; j < size; j++) {
            if (grid[row][j] != symbol) return false;
        }
        return true;
    }
    
    bool checkColumn(int col, CellState symbol) {
        for (int i = 0; i < size; i++) {
            if (grid[i][col] != symbol) return false;
        }
        return true;
    }
    
    bool checkDiagonal(CellState symbol) {
        bool diag1 = true, diag2 = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][i] != symbol) diag1 = false;
            if (grid[i][size - i - 1] != symbol) diag2 = false;
        }
        return diag1 || diag2;
    }
};
// Game Class
class Game {
private:
    Board board;
    Player player1, player2;
    Player* currentPlayer;

public:
    Game(string p1, string p2) 
        : board(3), player1(p1, CellState::X), player2(p2, CellState::O), currentPlayer(&player1) {}

    void play() {
        int row, col;
        while (true) {
            board.printBoard();
            cout << currentPlayer->name << "'s turn (" << (currentPlayer->symbol == CellState::X ? "X" : "O") << "): ";
            cin >> row >> col;

            if (!board.makeMove(row, col, currentPlayer->symbol)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            if (board.checkWin(currentPlayer->symbol)) {
                board.printBoard();
                cout << currentPlayer->name << " wins!\n";
                return;
            }

            if (board.isFull()) {
                board.printBoard();
                cout << "It's a draw!\n";
                return;
            }

            // Switch player
            currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
        }
    }
};
    
int main() {
    string p1, p2;
    cout << "Enter Player 1 name: ";
    cin >> p1;
    cout << "Enter Player 2 name: ";
    cin >> p2;

    Game game(p1, p2);
    game.play();

    return 0;
}