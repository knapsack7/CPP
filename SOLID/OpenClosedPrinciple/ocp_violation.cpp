/*
Open/Closed Principle (OCP) in C++)

📌 Principle Definition:

	Software entities (classes, modules, functions) should be open for extension but closed for modification.

This means that we should be able to add new functionality without modifying existing code, ensuring our system remains stable and maintainable.
*/
/*
🚨 Violation of OCP (Bad Example)

In this example, we have a DiscountCalculator that calculates discounts for different customers (Regular & Premium). 
However, every time a new customer type is introduced, we must modify the calculateDiscount() method, violating OCP.
*/

#include <iostream>
#include <memory>
using namespace std;

// ❌ BAD: Adding a new customer type requires modifying this class
class DiscountCalculator {
public:
    double calculateDiscount(string customerType, double amount) {
        if (customerType == "Regular") {
            return amount * 0.1;  // 10% discount for regular customers
        } 
        else if (customerType == "Premium") {
            return amount * 0.2;  // 20% discount for premium customers
        }
        return 0.0;  // No discount
    }
};

int main() {
    std::unique_ptr<DiscountCalculator> calculator = std::make_unique<DiscountCalculator>();
    cout << "Regular Customer Discount: " << calculator->calculateDiscount("Regular", 1000) << endl;
    cout << "Premium Customer Discount: " << calculator->calculateDiscount("Premium", 1000) << endl;

    return 0;
}

/*
🔴 Problems in this approach:
	1.	Violates OCP – Adding a new customer type (e.g., “VIP”) requires modifying calculateDiscount().
	2.	Hard to maintain – Every change requires modifying and testing the existing class.
	3.	High risk of bugs – Changes might break existing functionality.
*/