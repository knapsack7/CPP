/*
Polymorphism in C++ can be classified into two types:

Compile-time Polymorphism (Function Overloading & Operator Overloading)
Run-time Polymorphism (Function Overriding & Virtual Functions)
Polymorphism means "many forms." It allows a method, function, or object to behave differently based on the context. Polymorphism enables dynamic method resolution and method flexibility, making applications easier to extend and maintain.

Key Benefits of Polymorphism
Code Reusability: Write a single interface that works for multiple types.
Scalability: Add new functionalities with minimal code changes.
Maintainability: Reduce complexity and improve code clarity.
*/

//1. compile time polymorphism(function overloading)
/*
Compile-time polymorphism occurs when multiple functions in the same class share the same name but have different method signatures (parameters).
The method to be called is determined at compile time.
*/

// #include <iostream>
// using namespace std;

// class MathOperations {
// public:
//     // Function with two parameters
//     int add(int a, int b) {
//         return a + b;
//     }
    
//     // Function with three parameters (overloaded)
//     int add(int a, int b, int c) {
//         return a + b + c;
//     }
// };

// int main() {
//     MathOperations math;
//     cout << "Sum (2 numbers): " << math.add(5, 10) << endl;
//     cout << "Sum (3 numbers): " << math.add(5, 10, 15) << endl;
//     return 0;
// }

//2. Runtime Polymorphism (Function Overriding & Virtual Functions)

/*
Run-time polymorphism occurs when a subclass provides a specific implementation of a method already defined in its parent class.
The method to be called is determined at runtime using virtual functions.*/

// #include <iostream>
// using namespace std;

// class Animal {
// public:
//     virtual void makeSound() {
//         cout << "Animal makes a sound" << endl;
//     }
//     virtual ~Animal() = default;
// };

// class Dog : public Animal {
// public:
//     void makeSound() override {
//         cout << "Dog barks" << endl;
//     }
// };

// class Cat : public Animal {
// public:
//     void makeSound() override {
//         cout << "Cat meows" << endl;
//     }
// };

// int main() {
//     unique_ptr<Animal> myAnimal = make_unique<Dog>(); // Upcasting
//     myAnimal->makeSound();
    
//     myAnimal = make_unique<Cat>(); // Dynamic method dispatch
//     myAnimal->makeSound();

//     return 0;
// }


// Using Polymorphism with Abstract Classes

// Polymorphism is widely used with abstract classes, allowing multiple derived
// classes to share a common contract

// #include <iostream>
// using namespace std;

// class Vehicle {
// public:
//     virtual void start() = 0; // Pure virtual function
//     virtual ~Vehicle() = default; 
// };

// class Car : public Vehicle {
// public:
//     void start() override {
//         cout << "Car is starting..." << endl;
//     }
// };

// class Bike : public Vehicle {
// public:
//     void start() override {
//         cout << "Bike is starting..." << endl;
//     }
// };

// int main() {
//     unique_ptr<Vehicle> myVehicle = make_unique<Car>(); 
//     myVehicle->start();
    
//     myVehicle = make_unique<Bike>();
//     myVehicle->start();

//     return 0;
// }

// Real-World Example : Payment System
// A common real-world use case of polymorphism is in payment processing

#include <iostream>
using namespace std;

class Payment {
public:
    virtual void pay(double amount) = 0; // Pure virtual function
    virtual ~Payment() = default;
};

class CreditCardPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Credit Card" << endl;
    }
};

class PayPalPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using PayPal" << endl;
    }
};

int main() {
    unique_ptr<Payment> payment = make_unique<CreditCardPayment>();
    payment->pay(100.50);
    
    payment = make_unique<PayPalPayment>();
    payment->pay(200.75);

    return 0;
}
