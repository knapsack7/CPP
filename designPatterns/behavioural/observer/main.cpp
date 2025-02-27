#include<iostream>
#include<string>

class OrderObserver {
    public:
        virtual void update(const std::string& status) = 0;
        virtual ~OrderObserver() = default;
    };
    
    // Concrete Observers
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
    
    // Subject (Order)
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
    
    // Example Usage
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