#ifndef CART_H
#define CART_H


#include <vector>
#include "Product.h"
#include "DiscountStrategy.h"

class Cart{
private:
    std::vector<Product*> products;
    double total;

public:
    void addProducts(Product* product);

    void applyDiscount(DiscountStrategy* discount);

    double calculateTotal();

    ~Cart();
};

#endif //CART_H