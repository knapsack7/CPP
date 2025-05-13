#include "PlayerFactory.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

std::shared_ptr<Player> PlayerFactory::createHumanPlayer(const std::string& name, char marker) {
    return std::make_shared<HumanPlayer>(name, marker);
}

std::shared_ptr<Player> PlayerFactory::createAIPlayer(const std::string& name, char marker) {
    return std::make_shared<AIPlayer>(name, marker);
}
