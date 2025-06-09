#include <iostream>
#include "../include/account.h"
void transact(Account *pAccount){
    std::cout<< "Transaction started" << std::endl;
    std::cout<< "Initial balance: " << pAccount->getBalance() << std::endl;
    pAccount->deposit(100);
    pAccount->accumulateInterest();
    pAccount->withdraw(170);
    std::cout<< "Interest: " << pAccount->getInterestRate() << std::endl;
    std::cout<< "Final balance: " << pAccount->getBalance() << std::endl;
    std::cout<< "Transaction ended" << std::endl;
}