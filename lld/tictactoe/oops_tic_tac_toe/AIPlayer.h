#pragma once

#include "Player.h"
#include "Board.h"
#include <string>

/**
 * AIPlayer class - represents an AI player in the tic-tac-toe game
 * This class implements a computer opponent that makes automated moves
 */
class AIPlayer : public Player {
public:
    /**
     * Constructor for AIPlayer
     * @param name The name of the AI player
     * @param marker The symbol representing this player (typically 'X' or 'O')
     */
    AIPlayer(const std::string& name, char marker);

    /**
     * Destructor
     */
    virtual ~AIPlayer();

    /**
     * Make a move on the board
     * Implements AI strategy to choose the best move
     * @param board The game board to make a move on
     * @return True if the move was successful, false otherwise
     */
    bool makeMove(Board& board) override;
};

