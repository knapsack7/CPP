#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    virtual std::string getName() const = 0 ;
    virtual double getPrice() const = 0;
    virtual ~Product() {}
};

class Electronics : public Product {
private:
    std::string name;
    double price;
public:
    Electronics(const std::string& name, double price);
    std::string getName() const override;
    double getPrice() const override;
};

class Clothing : public Product {
private:
    std::string name;
    double price;
public:
    Clothing(const std::string& name, double price);
    std::string getName() const override;
    double getPrice() const override;
};

#endif //PRODUCT_H
