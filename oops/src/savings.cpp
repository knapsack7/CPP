#include "../include/savings.h"
#include <iostream>

Savings::Savings(const std::string& name, float balance, float rate): Account{name, balance}, mRate{rate}{
    std::cout<< "Savings(const std::string& name, float balance, float rate) called" << std::endl;
}

Savings::~Savings(){
    std::cout<< "~Savings() destructor called" << std::endl;
}

float Savings::getInterestRate() const{
    return mRate;
}
// but we cant access mBalance here because it is private in the base class
// so we need to make it protected in the base class
void Savings::accumulateInterest(){
    mBalance += (mBalance * mRate);
}