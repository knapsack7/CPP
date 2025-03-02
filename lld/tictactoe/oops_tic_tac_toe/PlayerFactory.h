#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#pragma once

#include <string>
#include <memory>
#include "Player.h"

/**
 * Factory class for creating different types of players (Human, AI)
 */
class PlayerFactory {
public:
    /**
     * Creates a human player
     * @param name Player's name
     * @param marker Player's marker symbol (X or O)
     * @return A shared pointer to the created human player
     */
    static std::shared_ptr<Player> createHumanPlayer(const std::string& name, char marker);

    /**
     * Creates an AI player
     * @param name Player's name
     * @param marker Player's marker symbol (X or O)
     * @return A shared pointer to the created AI player
     */
    static std::shared_ptr<Player> createAIPlayer(const std::string& name, char marker);
};

#endif // PLAYER_FACTORY_H

