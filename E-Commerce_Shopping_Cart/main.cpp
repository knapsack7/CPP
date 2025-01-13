/*
This is the entry point of the application
*/

#include <iostream>
#include "Product.h"
#include "Cart.h"
#include "Checkout.h"
#include "PercentageDiscount.h"
#include "FixedAmountDiscount.h"


int main(){
    Cart cart;

    /*Creating Products*/
    Product* laptop = new Electronics("Laptop", 10000);
    Product* shirt = new Clothing("Shirt", 1000);

    /*Adding products to the Cart*/
    cart.addProducts(laptop);
    cart.addProducts(shirt);

    /*Applying Discount*/
    DiscountStrategy* discount = new PercentageDiscount(10); // 10% discount

    /*Checkout Process*/
    Checkout checkout;
    checkout.processOrder(cart);

    /*Clean Up*/
    delete discount; // Only need to delete discount as Cart handles product cleanup
    discount = nullptr;
    
    return 0;

}