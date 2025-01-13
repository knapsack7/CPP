#include "Product.h"

// Electronics implementation
Electronics::Electronics(const std::string& name, double price) : name(name), price(price) {
}

std::string Electronics::getName() const {
    return name;
}

double Electronics::getPrice() const {
    return price;
}

// Clothing implementation
Clothing::Clothing(const std::string& name, double price) : name(name), price(price) {
}

std::string Clothing::getName() const {
    return name;
}

double Clothing::getPrice() const {
    return price;
}

