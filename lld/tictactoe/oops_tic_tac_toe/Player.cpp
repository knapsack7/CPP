#include "Player.h"

// Constructor implementation
Player::Player(const std::string& name, char marker) 
    : name(name), marker(marker) {
}

// Get the player's name
std::string Player::getName() const {
    return name;
}

// Get the player's marker symbol
char Player::getMarker() const {
    return marker;
}
