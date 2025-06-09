#pragma once
#include "account.h"

class Checking : public Account{
public:
    // So if ur child class has not its own data members, then u can use using keyword
    // to invoke base class constructor and destructor, inherits all the constructors and destructors
    using Account::Account;
    //Checking(const std::string& name, float balance);
    //using Account::Account;
    ~Checking();
    void withdraw(float amount);
};