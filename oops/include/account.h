#pragma once
#include <string>

class Account{
    std::string mName;
    int mAccNo;
    static int sAccNumGenerator;
public:
    Account(const std::string& name, float balance);
    virtual ~Account(); // must be virtual for polymorphism and to avoid memory leak
    const std::string getName() const;
    float getBalance() const;
    int getAccNo() const;

    virtual void accumulateInterest();
    virtual void withdraw(float amount);
    void deposit(float amount);

    virtual float getInterestRate() const;
protected:
    float mBalance;
};