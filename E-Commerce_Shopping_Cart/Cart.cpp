#include "Cart.h"

void Cart::addProducts(Product* product) {
    products.push_back(product);
}

void Cart::applyDiscount(DiscountStrategy* discount) {
    total = calculateTotal();
    total = discount->applyDiscount(total);
}

double Cart::calculateTotal() {
    total = 0;
    for (auto product: products)
        total += product->getPrice();
    return total;
}

Cart::~Cart() {
    for(auto product: products)
        delete product;
}

