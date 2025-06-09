#include "../include/checking.h"
#include <iostream>

// Checking::Checking(const std::string& name, float balance): Account{name, balance}{

// }

Checking::~Checking(){

}

void Checking::withdraw(float amount){
    if ((mBalance - amount) > 50){
        Account::withdraw(amount);
    } else {
        std::cout << "Insufficient balance" << std::endl;
    }
}