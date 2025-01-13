#ifndef PERCENTDISCOUNT_H
#define PERCENTDISCOUNT_H

#include "DiscountStrategy.h"

class PercentageDiscount : public DiscountStrategy {
private:
    double percentage;
public:
    PercentageDiscount(double percentage) : percentage(percentage){}
    double applyDiscount(double price) override{
        return price - (price * percentage / 100);
    }
};

#endif