/*
✅ Correct Approach (OCP-Compliant Solution)

We use polymorphism and inheritance to make the system extensible without modifying existing code.
*/

#include <iostream>
#include <memory>  // For smart pointers
using namespace std;

// ✅ Abstract base class for discount strategy
class DiscountStrategy {
public:
    virtual double getDiscount(double amount) = 0;  // Pure virtual function
    virtual ~DiscountStrategy() {} // Must be declared for polymorphic type Classes for no memory-leak problem
};

// ✅ Concrete strategy for regular customers
class RegularDiscount : public DiscountStrategy {
public:
    double getDiscount(double amount) override {
        return amount * 0.1;  // 10% discount
    }
};

// ✅ Concrete strategy for premium customers
class PremiumDiscount : public DiscountStrategy {
public:
    double getDiscount(double amount) override {
        return amount * 0.2;  // 20% discount
    }
};

// ✅ Adding a new customer type (VIP) without modifying existing code
class VIPDiscount : public DiscountStrategy {
public:
    double getDiscount(double amount) override {
        return amount * 0.3;  // 30% discount
    }
};

// ✅ Discount Calculator that is open for extension but closed for modification
class DiscountCalculator {
public:
    static double calculateDiscount(unique_ptr<DiscountStrategy>& strategy, double amount) {
        return strategy->getDiscount(amount);
    }
};

int main() {
    unique_ptr<DiscountStrategy> regular = make_unique<RegularDiscount>();
    unique_ptr<DiscountStrategy> premium = make_unique<PremiumDiscount>();
    unique_ptr<DiscountStrategy> vip = make_unique<VIPDiscount>();
    // since calculateDiscount is static function we dont need to have DiscountCalculator class object to invoke it. 
    cout << "Regular Discount: " << DiscountCalculator::calculateDiscount(regular, 1000) << endl;
    cout << "Premium Discount: " << DiscountCalculator::calculateDiscount(premium, 1000) << endl;
    cout << "VIP Discount: " << DiscountCalculator::calculateDiscount(vip, 1000) << endl;

    return 0;
}

/*
🔥 Advantages of This Approach

✅ OCP-Compliant: We can add new discount types without modifying DiscountCalculator.
✅ Polymorphism-Based Design: DiscountCalculator only depends on DiscountStrategy and does not need changes for new strategies.
✅ Scalability: We can add StudentDiscount, SeniorCitizenDiscount, etc., without modifying existing classes.
*/