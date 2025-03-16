#include <iostream>
#include <memory> 
using namespace std;

// Defining an interface
class Vehicle {
public:
    virtual void start() = 0; // Pure virtual function
    virtual void stop() = 0;  // Pure virtual function
    /*In C++, when using polymorphism, the base class (interface) should have a virtual destructor to ensure proper cleanup of derived class objects.
    Without a virtual destructor, deleting a derived class object through a base class pointer can lead to undefined behavior.*/
    virtual ~Vehicle() = default;
};

// Implementing the Vehicle interface in a Car class
class Car : public Vehicle {
public:
    void start() override {
        cout << "Car is starting..." << endl;
    }
    
    void stop() override {
        cout << "Car is stopping..." << endl;
    }
};

// int main() {
//     unique_ptr<Vehicle> myCar = make_unique<Car>(); // Polymorphism: Interface reference
//     myCar->start();
//     myCar->stop();
    
//     return 0;
// }

// Multiple inheritance with Interfaces

// First interface
class Flyable {
public:
    virtual void fly() = 0;
    virtual ~Flyable() = default;
};

// Second interface
class Drivable {
public:
    virtual void drive() = 0;
    virtual ~Drivable() = default;
};

// Implementing multiple interfaces
class FlyingCar : public Flyable, public Drivable {
public:
    void fly() override {
        cout << "FlyingCar is flying..." << endl;
    }
    
    void drive() override {
        cout << "FlyingCar is driving..." << endl;
    }
};

// int main(){
//     unique_ptr<FlyingCar> myVehicle = make_unique<FlyingCar>();
//     myVehicle->fly();
//     myVehicle->drive();

//     return 0;
// }

// Providing Default Implementations in Interfaces

class Animal {
public:
    virtual void sound() = 0;
    void sleep() { // Default method
        cout << "Sleeping..." << endl;
    }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void sound() override {
        cout << "Dog barks" << endl;
    }
};

// int main(){
//     unique_ptr<Dog> myDog = make_unique<Dog>();
//     myDog->sound();
//     myDog->sleep();
//     return 0;
// }

// Real World Example

class Payment {
public:
    virtual void pay(double amount) = 0;
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
    unique_ptr<Payment> payment1 = make_unique<CreditCardPayment>();
    payment1->pay(100.50);
    
    unique_ptr<Payment> payment2 = make_unique<PayPalPayment>();
    payment2->pay(200.75);
    
    return 0;
}