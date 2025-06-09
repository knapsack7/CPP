#include <iostream>

class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
    ~Base() { std::cout << "Base destructor" << std::endl; }
    int x;
};

// Virtual inheritance to prevent multiple Base construction
class Derived1 : virtual public Base {
public:
    Derived1() { std::cout << "Derived1 constructor" << std::endl; }
    ~Derived1() { std::cout << "Derived1 destructor" << std::endl; }
};

// Virtual inheritance to prevent multiple Base construction
class Derived2 : virtual public Base {
public:
    Derived2() { std::cout << "Derived2 constructor" << std::endl; }
    ~Derived2() { std::cout << "Derived2 destructor" << std::endl; }
};

// Final class inheriting from both Derived1 and Derived2
class Final : public Derived1, public Derived2 {
public:
    Final() { std::cout << "Final constructor" << std::endl; }
    ~Final() { std::cout << "Final destructor" << std::endl; }
};

int main() {
    Final f;
    
    // Without virtual inheritance, this would be ambiguous
    f.x = 10;  // Works because there's only one Base subobject
    
    std::cout << "Value of x: " << f.x << std::endl;
    return 0;
} 