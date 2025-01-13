#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <iostream>
#include "Cart.h"

class Checkout {
public:
    void processOrder(Cart& cart){
        double total = cart.calculateTotal();
        std::cout<< "Total after discount : $" << total << std::endl;
        // Process payment and order confirmation 
    }
};


#endif //CHECKOUT_H