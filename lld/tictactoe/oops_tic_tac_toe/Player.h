#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Board; // Forward declaration of Board class

/**
 * Abstract Player class representing a player in a Tic Tac Toe game.
 * This class provides the interface that all concrete player types must implement.
 */
class Player {
public:
    /**
     * Constructor with player name and marker symbol
     */
    Player(const std::string& name, char marker);
    
    /**
     * Virtual destructor for proper cleanup of derived classes
     */
    virtual ~Player() = default;
    
    /**
     * Get the player's name
     */
    std::string getName() const;
    
    /**
     * Get the player's marker symbol (X or O)
     */
    char getMarker() const;
    
    /**
     * Pure virtual function that must be implemented by concrete players
     * Makes a move on the given board
     * @param board The game board to make a move on
     * @return true if move was successful, false otherwise
     */
    virtual bool makeMove(Board& board) = 0;

protected:
    std::string name;  // Player name
    char marker;       // Player marker (X or O)
};

#endif // PLAYER_H

