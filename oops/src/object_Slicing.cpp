#include <iostream>

class Base {
public:
    virtual void print() {
        std::cout << "Base::print()" << std::endl;
    }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void print() override {
        std::cout << "Derived::print()" << std::endl;
    }
};

int main() {
    // 1. Object Slicing Example
    Derived d;
    Base b = d;  // Object slicing occurs here
    b.print();   // Calls Base::print() - slicing lost the Derived part
    
    // 2. Polymorphism with Pointer
    Base* ptr = &d;
    ptr->print();  // Calls Derived::print() - polymorphism works
    
    // 3. Polymorphism with Reference
    Base& ref = d;
    ref.print();   // Calls Derived::print() - polymorphism works
    
    return 0;
} 

/*
   Derived Object in Memory:
   +----------------+
   | Base part      |  <- Contains vtable pointer
   +----------------+
   | Derived part   |  <- Additional members
   +----------------+

   When sliced (Base b = d):
   +----------------+
   | Base part      |  <- Only this is copied, vtable points to Base
   +----------------+
*/