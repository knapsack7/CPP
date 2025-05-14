#include<iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "concreteObservers.h"

// using namespace std; // Removed to avoid polluting global namespace in header

class Order {
private:
    //std::vector<OrderObserver*> observers;
    std::vector<std::unique_ptr<OrderObserver>> observers;
public:
    //void addObserver(OrderObserver* observer) { observers.push_back(observer); }
    void addObserver(std::unique_ptr<OrderObserver> observer) {observers.push_back(std::move(observer));}
    // void removeObserver(OrderObserver* observer) {
    //     observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    // }
    void removeObserver(std::unique_ptr<OrderObserver> observer) {
        // remove need iterator to pass as argument which you need to delete
        auto it = std::find_if(
        observers.begin(), observers.end(),
        [&observer](const std::unique_ptr<OrderObserver>& ele) { return ele.get() == observer.get(); }
        );
        if (it != observers.end())
            observers.erase(it);
    }


    void updateStatus(const std::string& status) {
        std::cout << "Order Status Updated: " << status << std::endl;
        for (std::unique_ptr<OrderObserver> &observer : observers) {
            observer->update(status);
        }
    }
};