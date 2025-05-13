#pragma once

#include "Player.h"
#include "Board.h"
#include <string>

/**
 * HumanPlayer class - represents a human player in the tic-tac-toe game
 * This class handles getting input from the user to make moves on the board
 */
class HumanPlayer : public Player {
public:
    /**
     * Constructor for HumanPlayer
     * @param name The name of the player
     * @param marker The symbol representing this player (typically 'X' or 'O')
     */
    HumanPlayer(const std::string& name, char marker);

    /**
     * Destructor
     */
    virtual ~HumanPlayer();

    /**
     * Make a move on the board
     * @param board The game board to make a move on
     * @return True if the move was successful, false otherwise
     */
    bool makeMove(Board& board) override;
};

