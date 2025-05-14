# Observer Pattern

## When to Use the Observer Pattern (System/Embedded Context)

The **Observer Pattern** is especially useful in system engineering and embedded systems when you have a one-to-many relationship between components, so that when one component (the **Subject**) changes its state, all its dependents (**Observers**) are notified and updated automatically.

### Typical Scenarios in Embedded/Systems Engineering
- When a hardware event (e.g., sensor value change, interrupt, or GPIO pin state) must notify multiple software modules or tasks.
- When a central controller needs to broadcast status updates to several subsystems (e.g., display, logger, communication module).
- When you want to decouple hardware drivers from application logic, allowing flexible extension and maintenance.

## How to Memorize When to Use Observer Pattern

**Mnemonic:**
> "When one event, many modules must react."

Or simply remember:
- **Event-driven systems**: If you need to notify multiple modules/tasks when a hardware or software event occurs, Observer is a good fit.
- **Loose coupling**: If you want to avoid hard-wiring dependencies between drivers and application logic.

**Embedded/Systems Real-world Analogies:**
- **Interrupt Service Routine (ISR) broadcasting**: When an ISR triggers, multiple modules (e.g., logger, actuator, communication) may need to react.
- **Sensor network**: When a sensor value changes, several modules (e.g., display, alarm, data logger) need to be notified.
- **RTOS event flags**: When a flag is set, multiple tasks may be waiting and should be notified.

## Example in This Folder

This folder contains a C++ implementation of the Observer pattern for an order system. In embedded terms, think of **Order** as a hardware device or event source, and **Customer**, **Seller**, and **Logistics** as different software modules or tasks that need to react to status changes.

### Example Usage (Embedded Analogy)
```cpp
Order order; // Could represent a hardware device or event source
Customer customer; // Could represent a display module
Seller seller;     // Could represent a logger
Logistics logistics; // Could represent a communication module

order.addObserver(&customer);
order.addObserver(&seller);
order.addObserver(&logistics);

order.updateStatus("Sensor threshold crossed");  // Notifies all observers
```

## Summary Table
| Use Observer Pattern When...                | Don't Use When...                        |
|---------------------------------------------|------------------------------------------|
| Many modules need to react to an event      | Only one module needs to react           |
| You want to decouple event source and sinks | Tight coupling is acceptable             |
| You need dynamic subscription/unsubscription| All dependencies are static and simple   |

---

**Remember:** Observer = "One-to-many notification of events or changes."

# Observer Pattern - Embedded/System Engineering Example

## Overview
This project demonstrates the **Observer Pattern** using a simplified system where multiple modules (observers) are notified when a central event (subject) occurs. This is analogous to how embedded systems handle events, interrupts, or sensor changes.

## Design Pattern Used
The **Observer Pattern** is used to:
- Notify multiple modules (e.g., display, logger, communication) when an event occurs.
- Decouple the event source (e.g., hardware driver) from the modules that react to it.
- Allow easy extension: add new modules without changing the event source code.

## System Components
### 1. **Observer Interface (`OrderObserver`)**
   - Defines the `update()` method that modules must implement.

### 2. **Concrete Observers (`Customer`, `Seller`, `Logistics`)**
   - Implement the `update()` method to receive event notifications.

### 3. **Subject (`Order`)**
   - Maintains a list of observers and notifies them when the event occurs.

## Embedded/System Engineering Analogy
- **Order** = Event source (e.g., sensor, hardware driver, ISR)
- **Observers** = Software modules/tasks (e.g., display, logger, communication handler)
- **updateStatus()** = Event trigger (e.g., sensor value change, interrupt fired)

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

See `main.cpp` for the full implementation.

---

**In summary:**
- Use the Observer pattern in embedded/systems engineering when you want multiple modules to react to a single event or state change, and you want to keep your code modular and maintainable.

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