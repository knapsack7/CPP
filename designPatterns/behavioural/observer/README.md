# Observer Pattern - Amazon Order Status Updates

## Overview
This project demonstrates the **Observer Pattern** using a simplified Amazon order tracking system. When an order status changes, multiple stakeholders (**Customer, Seller, and Logistics**) are notified in real-time without being tightly coupled to the order system.

## Design Pattern Used
The **Observer Pattern** is used to:
- Notify multiple observers (Customer, Seller, Logistics) when the order status changes.
- Decouple the subject (Order) from the observers, allowing flexible extensions.
- Ensure real-time updates without modifying existing code when new observers are added.

## System Components
### 1. **Observer Interface (`OrderObserver`)**
   - Defines the `update()` method that observers must implement.

### 2. **Concrete Observers (`Customer`, `Seller`, `Logistics`)**
   - Implement the `update()` method to receive order status notifications.

### 3. **Subject (`Order`)**
   - Maintains a list of observers and notifies them when the order status updates.

## UML Diagram

      +------------------+
      |   OrderObserver  |<----------------+
      +------------------+                 |
              ▲                            |
  +-----------------+     +-----------------+     +-----------------+
  |    Customer     |     |    Seller       |     |   Logistics      |
  +-----------------+     +-----------------+     +-----------------+
              ▲                            ▲                     ▲
              |                            |                     |
      +---------------------------------------------------------+
      |                        Order                           |
      +---------------------------------------------------------+
      | - observers: vector<OrderObserver*>                     |
      | + addObserver(OrderObserver*)                           |
      | + removeObserver(OrderObserver*)                        |
      | + updateStatus(string)                                  |
      +---------------------------------------------------------+

## Code Implementation (C++)

### **OrderObserver.h**
```cpp
class OrderObserver {
public:
    virtual void update(const std::string& status) = 0;
    virtual ~OrderObserver() = default;
};

#include <iostream>
#include "OrderObserver.h"

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

#include <vector>
#include <algorithm>
#include "OrderObserver.h"

class Order {
private:
    std::vector<OrderObserver*> observers;
public:
    void addObserver(OrderObserver* observer) { observers.push_back(observer); }
    void removeObserver(OrderObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    
    void updateStatus(const std::string& status) {
        std::cout << "Order Status Updated: " << status << std::endl;
        for (OrderObserver* observer : observers) {
            observer->update(status);
        }
    }
};

#include "Order.h"
#include "OrderObserver.h"
#include "ConcreteObservers.h"

int main() {
    Order order;
    Customer customer;
    Seller seller;
    Logistics logistics;

    order.addObserver(&customer);
    order.addObserver(&seller);
    order.addObserver(&logistics);

    order.updateStatus("Shipped");  // Notifies all observers

    return 0;
}