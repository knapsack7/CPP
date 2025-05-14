#include "concrete_state.h"
#include <iostream>

void IdleState::handle() {
    std::cout << "Device is idle.\n";
}

void ActiveState::handle() {
    std::cout << "Device is active.\n";
}

void ErrorState::handle() {
    std::cout << "Device is in error state!\n";
}