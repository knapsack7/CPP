#include <iostream>
#include "../include/account.h"
#include "../include/checking.h"


void transact(Account *pAccount){
    std::cout<< "Transaction started" << std::endl;
    std::cout<< "Initial balance: " << pAccount->getBalance() << std::endl;
    pAccount->deposit(100);
    pAccount->accumulateInterest();
    Checking *pCheck = dynamic_cast<Checking*>(pAccount);
    // dynamic cast returns nullptr for pointers if the cast is not possible
    // so we can check if the cast is successful
    if (pCheck){
        std::cout<< "Min balance of Checking : " << pCheck->getMinBalance() << std::endl;
    }
    pAccount->withdraw(170);
    std::cout<< "Interest: " << pAccount->getInterestRate() << std::endl;
    std::cout<< "Final balance: " << pAccount->getBalance() << std::endl;
    std::cout<< "Transaction ended" << std::endl;
}

// dynammic cast also works with references


void transact(Account &pAccount){
    std::cout<< "Transaction started" << std::endl;
    std::cout<< "Initial balance: " << pAccount.getBalance() << std::endl;
    pAccount.deposit(100);
    pAccount.accumulateInterest();
    Checking &pCheck = dynamic_cast<Checking&>(pAccount);
    // dynamic cast returns exception (bad_cast) for reference if the cast is not possible
    // so we can check if the cast is successful
    std::cout<< "Min balance of Checking : " << pCheck.getMinBalance() << std::endl;
    pAccount.withdraw(170);
    std::cout<< "Interest: " << pAccount.getInterestRate() << std::endl;
    std::cout<< "Final balance: " << pAccount.getBalance() << std::endl;
    std::cout<< "Transaction ended" << std::endl;
}