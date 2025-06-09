#include <iostream>

class Base {
public:
    // Pure virtual function declaration
    virtual void pureVirtual() = 0;
    
    // Implementation of pure virtual function
    void pureVirtualImpl() {
        std::cout << "Base::pureVirtual implementation" << std::endl;
    }

    // Regular virtual function
    virtual void regularVirtual() {
        std::cout << "Base::regularVirtual" << std::endl;
    }
};

// Provide implementation for pure virtual function
void Base::pureVirtual() {
    std::cout << "Base::pureVirtual implementation" << std::endl;
}

class Derived : public Base {
public:
    // Must implement pure virtual function
    void pureVirtual() override {
        // Can call base implementation
        Base::pureVirtual();
        std::cout << "Derived::pureVirtual" << std::endl;
    }

    // Optional to override regular virtual
    void regularVirtual() override {
        std::cout << "Derived::regularVirtual" << std::endl;
    }
};

int main() {
    // Base b;  // Error: Cannot instantiate abstract class
    
    Derived d;
    d.pureVirtual();      // Calls Derived implementation
    d.regularVirtual();   // Calls Derived implementation
    
    // Using base pointer
    Base* ptr = &d;
    ptr->pureVirtual();   // Calls Derived implementation
    ptr->regularVirtual(); // Calls Derived implementation
    
    return 0;
} 