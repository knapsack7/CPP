#include "../include/account.h"
#include <iostream>

int Account::sAccNumGenerator = 1000;


Account::Account(const std::string& name, float balance): mName{name}, mBalance{balance}, mAccNo{++sAccNumGenerator}{
    std::cout<< "Account(const std::string& name, float balance) called" << std::endl;
}

Account::~Account(){
    std::cout<< "~Account() destructor called" << std::endl;

}

const std::string Account::getName() const{
    return mName;
}

float Account::getBalance() const{
    return mBalance;
}

int Account::getAccNo() const{
    return mAccNo;
}

void Account::accumulateInterest(){
}

void Account::withdraw(float amount){
    if (amount < mBalance){
         mBalance -= amount;
    } else {
        std::cout << "Insufficient balance" << std::endl;
    }
}

void Account::deposit(float amount){
    mBalance += amount;
}

float Account::getInterestRate() const{
    return 0.0f;
}