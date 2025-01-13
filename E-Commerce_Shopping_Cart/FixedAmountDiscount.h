#ifndef FIXEDAMOUNTDISCOUNT_H
#define FIXEDAMOUNTDISCOUNT_H

#include "DiscountStrategy.h"

class FixedAmountDiscount : public DiscountStrategy {
private:
    double amount;
public:
    FixedAmountDiscount(double amount) : amount(amount){}
    double applyDiscount(double price) override {
        return price - amount;
    }
};


#endif // FIXEDAMOUNTDISCOUNT_H