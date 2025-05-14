#include <iostream>
#include "orderObserver.h"

class Customer : public OrderObserver {
public:
    void update(const std::string& status) override {
        std::cout << "Customer notified: Order is now " << status << std::endl;
    }
};

class Seller : public OrderObserver {
public:
    void update(const std::string& status) override {
        std::cout << "Seller notified: Order status changed to " << status << std::endl;
    }
};

class Logistics : public OrderObserver {
public:
    void update(const std::string& status) override {
        std::cout << "Logistics team notified: Order is now " << status << std::endl;
    }
};