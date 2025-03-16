#include <iostream>
using namespace std;

// Parent class
// class Animal {
// public:
//     string name;
//     void eat() {
//         cout << name << " is eating..." << endl;
//     }
// };

// Child class
// class Dog : public Animal {
// public:
//     void bark() {
//         cout << name << " is barking..." << endl;
//     }
// };

// int main() {
//     unique_ptr<Dog> myDog = make_unique<Dog>();
//     myDog->name = "Buddy";
//     myDog->eat(); // Inherited from Animal class
//     myDog->bark(); // Defined in Dog class
//     return 0;
// }

// 1. Single inheritance
// A subclass inherits from one superclass

// class Parent {
// public:
//     void show() {
//         cout << "This is the parent class" << endl;
//     }
// };

// class Child : public Parent {
// public:
//     void display() {
//         cout << "This is the child class" << endl;
//     }
// };

//2. Multilevel Inheritance
// A subclass inherits from another class, from a chain.

// class Grandparent {
// public:
//     void show() {
//         cout << "Grandparent class" << endl;
//     }
// };

// class Parent : public Grandparent {
// public:
//     void display() {
//         cout << "Parent class" << endl;
//     }
// };

// class Child : public Parent {
// public:
//     void print() {
//         cout << "Child class" << endl;
//     }
// };

// 3. Hierarchical Inheritance
// A single parent class has multiple child class

// class Parent {
// public:
//     void show() {
//         cout << "Parent class" << endl;
//     }
// };

// class Child1 : public Parent {
// public:
//     void display() {
//         cout << "Child1 class" << endl;
//     }
// };

// class Child2 : public Parent {
// public:
//     void print() {
//         cout << "Child2 class" << endl;
//     }
// };

// 4. Multiple Inheritance

// class Parent1 {
// public:
//     void show1() {
//         cout << "Parent1 class" << endl;
//     }
// };

// class Parent2 {
// public:
//     void show2() {
//         cout << "Parent2 class" << endl;
//     }
// };

// class Child : public Parent1, public Parent2 {
// };

// Method Overriding in Inheritance

// class Animal {
// public:
//     virtual void makeSound() {
//         cout << "Animal makes a sound" << endl;
//     }
// };

// class Dog : public Animal {
// public:
//     void makeSound() override {
//         cout << "Dog barks" << endl;
//     }
// };

// int main() {
//     unique_ptr<Animal> myAnimal = make_unique<Dog>(); // Polymorphism
//     myAnimal->makeSound();
//     return 0;
// }

// The super Equivalent : Using Base Class Constructor in C++
// class Animal {
// public:
//     Animal() {
//         cout << "Animal Constructor" << endl;
//     }
//     virtual void makeSound() {
//         cout << "Animal makes a sound" << endl;
//     }
// };

// class Dog : public Animal {
// public:
//     Dog() {
//         cout << "Dog Constructor" << endl;
//     }
//     void makeSound() override{
//         Animal::makeSound(); // Calls parent method
//         cout << "Dog barks" << endl;
//     }
// };

// int main() {
//     Dog myDog;
//     myDog.makeSound();
//     return 0;
// }

// REAL WORLD EXAMPLE: EMPLOYEE MANAGEMENT SYSTEM
class Employee {
public:
    string name;
    double salary;
    
    Employee(string name, double salary) {
        this->name = name;
        this->salary = salary;
    }
    void displayDetails() {
        cout << "Employee: " << name << ", Salary: " << salary << endl;
    }
};

class Manager : public Employee {
public:
    double bonus;
    
    Manager(string name, double salary, double bonus) : Employee(name, salary) {
        this->bonus = bonus;
    }
    void displayDetails() {
        Employee::displayDetails();
        cout << "Bonus: " << bonus << endl;
    }
};

int main() {
    unique_ptr<Manager> manager = make_unique<Manager>("Alice", 70000, 10000);
    manager->displayDetails();
    return 0;
}