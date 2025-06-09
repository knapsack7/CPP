#include "../include/checking.h"
#include <iostream>

Checking::Checking(const std::string& name, float balance, float minBalance): Account{name, balance}, mMinBalance{minBalance}{
    std::cout<< "Checking constructor called" << std::endl;
}

Checking::~Checking(){

}

void Checking::withdraw(float amount){
    if ((mBalance - amount) > mMinBalance){
        Account::withdraw(amount);
    } else {
        std::cout << "Insufficient balance" << std::endl;
    }
}

float Checking::getMinBalance() const{
    return mMinBalance;
}