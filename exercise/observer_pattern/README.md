# Observer Pattern

## Intent
The **Observer Pattern** defines a one-to-many dependency between objects so that when one object (the subject) changes state, all its dependents (observers) are notified and updated automatically.

## When to Use
- When changes to one object require changing others, but you don't know how many objects need to be changed.
- When an object should be able to notify other objects without making assumptions about who these objects are.
- When you want to decouple the subject from its observers to promote loose coupling.

## Why Use It?
- **Event-driven systems:** Useful for notifying multiple modules/tasks when a hardware or software event occurs.
- **Loose coupling:** Subject and observers are independent, making code more modular and maintainable.
- **Dynamic subscription:** Observers can subscribe/unsubscribe at runtime.

## Embedded/Systems Example Use Cases
- Notifying multiple modules when a sensor value changes (e.g., display, logger, alarm).
- Broadcasting hardware interrupt events to several software components.
- Updating multiple displays or communication modules when system status changes.

## Example: Order Status Notification in C++

### 1. Observer Interface
```cpp
class OrderObserver {
public:
    virtual void update(const std::string& status) = 0;
    virtual ~OrderObserver() = default;
};
```

### 2. Concrete Observers
```cpp
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
```

### 3. Subject (Order)
```cpp
#include <vector>
#include <algorithm>

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
```

### 4. Usage
```cpp
Order order;
Customer customer;
Seller seller;
Logistics logistics;

order.addObserver(&customer);
order.addObserver(&seller);
order.addObserver(&logistics);

order.updateStatus("Shipped");  // Notifies all observers
```

## Summary Table
| Use Observer Pattern When...                | Don't Use When...                        |
|---------------------------------------------|------------------------------------------|
| Many objects need to react to state changes | Only one object needs to react           |
| You want to decouple subject and observers  | Tight coupling is acceptable             |
| You need dynamic subscription/unsubscription| All dependencies are static and simple   |

## Mnemonic
> "When one changes, many must know."

---

**In summary:**
The Observer Pattern is ideal for event-driven embedded and systems applications where multiple modules need to react to changes in a decoupled and flexible way. 