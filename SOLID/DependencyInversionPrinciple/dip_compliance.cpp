#include <iostream>
#include <memory>

/*
✅ Correct Approach (DIP-Compliant Solution)

We create an abstraction (interface) that both high-level and low-level modules depend on.
This makes the system more flexible and maintainable.

Key improvements:
1. Created IPayment interface as an abstraction
2. PaymentProcessor depends on the interface, not concrete implementation
3. Easy to add new payment methods without modifying existing code
4. Follows Open/Closed Principle
*/

// Abstract interface that both high and low level modules depend on
class IPayment {
public:
    virtual void pay(int amount) = 0;
    virtual ~IPayment() = default;
};

// Low-level module implementing the interface
class PayPalPayment : public IPayment {
public:
    void pay(int amount) override {
        std::cout << "Processing payment of $" << amount << " using PayPal." << std::endl;
    }
};

// Another low-level module implementing the same interface
class StripePayment : public IPayment {
public:
    void pay(int amount) override {
        std::cout << "Processing payment of $" << amount << " using Stripe." << std::endl;
    }
};

// High-level module depending on abstraction (interface)
class PaymentProcessor {
private:
    std::unique_ptr<IPayment> payment;
public:
    // Constructor injection of the payment dependency
    PaymentProcessor(std::unique_ptr<IPayment> payment) : payment(std::move(payment)) {}
    
    void processPayment(int amount) {
        payment->pay(amount);
    }
};

int main() {
    // Using PayPal
    auto paypalPayment = std::make_unique<PayPalPayment>();
    PaymentProcessor paypalProcessor(std::move(paypalPayment));
    paypalProcessor.processPayment(100);

    // Using Stripe
    auto stripePayment = std::make_unique<StripePayment>();
    // move used to transfer ownership of the object to the PaymentProcessor object
    // To enforce the space optimization as it steal pointer not copy the data.
    PaymentProcessor stripeProcessor(std::move(stripePayment));
    stripeProcessor.processPayment(200);

    return 0;
}