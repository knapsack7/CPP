#include <iostream>

/*

The Dependency Inversion Principle states that:
High-level modules should not depend on low-level modules. Both should depend on abstractions.
Abstractions should not depend on details. Details should depend on abstractions.


Here, the PaymentProcessor(high-level module) class directly depends on PayPalPayment(low-level module),
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