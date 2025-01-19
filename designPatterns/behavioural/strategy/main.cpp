#include <iostream>
#include <memory>

// Strategy Interface
class PaymentStrategy {
public:
    virtual void pay(int amount) const = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategies
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paid " << amount << " using Credit Card." << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paid " << amount << " using PayPal." << std::endl;
    }
};

class BitcoinPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paid " << amount << " using Bitcoin." << std::endl;
    }
};

// Context
class PaymentContext {
private:
    std::unique_ptr<PaymentStrategy> strategy;

public:
    explicit PaymentContext(std::unique_ptr<PaymentStrategy> strat) : strategy(std::move(strat)) {}

    void setStrategy(std::unique_ptr<PaymentStrategy> strat) {
        strategy = std::move(strat);
    }

    void executePayment(int amount) const {
        if (strategy) {
            strategy->pay(amount);
        } else {
            std::cout << "No payment strategy set." << std::endl;
        }
    }
};

// Example Usage
int main() {
    int amount = 100;

    // Using Credit Card
    auto creditCardPayment = std::make_unique<CreditCardPayment>();
    PaymentContext context(std::move(creditCardPayment));
    context.executePayment(amount);

    // Switching to PayPal
    auto paypalPayment = std::make_unique<PayPalPayment>();
    context.setStrategy(std::move(paypalPayment));
    context.executePayment(amount);

    // Switching to Bitcoin
    auto bitcoinPayment = std::make_unique<BitcoinPayment>();
    context.setStrategy(std::move(bitcoinPayment));
    context.executePayment(amount);

    return 0;
}

