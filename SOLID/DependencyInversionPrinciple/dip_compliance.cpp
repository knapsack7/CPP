#include <iostream>
using namespace std;


/*
We introduce an interface (abstract class) 
IPayment so that PaymentProcessor depends on an abstraction, not a concrete class.

🔥 Key Benefits of Using DIP

✅ Decoupling: PaymentProcessor does not depend on specific payment implementations.
✅ Scalability: We can add GooglePayPayment, ApplePayPayment, etc., without modifying PaymentProcessor.
✅ Flexibility: We can change dependencies at runtime using dependency injection.
✅ Testability: We can mock IPayment for unit testing.

*/

// Step 1: Define an interface (Abstraction)
class IPayment {
public:
    virtual void pay(int amount) = 0;  // Pure virtual function
    virtual ~IPayment() {}  // Virtual destructor
};

// Step 2: Implement different payment methods
class PayPalPayment : public IPayment {
public:
    void pay(int amount) override {
        cout << "Processing payment of $" << amount << " using PayPal." << endl;
    }
};

class StripePayment : public IPayment {
public:
    void pay(int amount) override {
        cout << "Processing payment of $" << amount << " using Stripe." << endl;
    }
};

// Step 3: High-level module depends on abstraction
class PaymentProcessor {
private:
    IPayment* payment;  // Dependency injected via constructor
public:
    PaymentProcessor(IPayment* p) : payment(p) {}

    void processPayment(int amount) {
        payment->pay(amount);
    }
};

int main() {
    // PayPal Payment
    PayPalPayment paypal;
    PaymentProcessor processor1(&paypal);
    processor1.processPayment(100);

    // Stripe Payment
    StripePayment stripe;
    PaymentProcessor processor2(&stripe);
    processor2.processPayment(200);

    return 0;
}