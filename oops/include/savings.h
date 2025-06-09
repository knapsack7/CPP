#pragma once
#include "account.h"

class Savings: public Account{
    float mRate;
public:
    Savings(const std::string& name, float balance, float rate);
    ~Savings();
    float getInterestRate() const;
    void accumulateInterest();
};