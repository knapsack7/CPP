#include <iostream>

/*
Here, the PaymentProcessor class directly depends on PayPalPayment,
which makes it tightly coupled and hard to extend.

Problems with this approach:
1.	Tightly coupled: PaymentProcessor is hardcoded to use PayPalPayment.
2.	Not flexible: If we want to support StripePayment, we must modify PaymentProcessor.
3.	Violates Open/Closed Principle (OCP): Every new payment method requires changes in PaymentProcessor.

*/

class PayPalPayment {
public:
    void pay(int amount) {
        std::cout << "Processing payment of $" << amount << " using PayPal." << std::endl;
    }
};

class PaymentProcessor {
private:
    PayPalPayment payment;  // Direct dependency on PayPal
public:
    void processPayment(int amount) {
        payment.pay(amount);
    }
};

int main() {
    PaymentProcessor processor;
    processor.processPayment(100);
    return 0;
}