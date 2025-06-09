#include <iostream>

/*
 * KEY INSIGHTS ABOUT PURE VIRTUAL FUNCTIONS AND INHERITANCE:
 * 
 * 1. Abstract Class Chain:
 *    - If a class inherits from an abstract class but doesn't implement all pure virtual functions,
 *      it remains abstract
 *    - This creates a chain of abstract classes until all pure virtual functions are implemented
 * 
 * 2. Instantiation Rules:
 *    - You cannot create objects of abstract classes
 *    - A class must implement ALL pure virtual functions to become concrete
 *    - Abstractness propagates through inheritance until all pure virtual functions are implemented
 * 
 * 3. Inheritance Behavior:
 *    - A class can be abstract even if it doesn't declare any pure virtual functions itself,
 *      just by inheriting them
 *    - This is useful for creating intermediate abstract classes that provide some implementation
 *      but still require derived classes to implement certain functions
 * 
 * 4. Implementation Requirements:
 *    - Derived classes MUST implement all pure virtual functions to become concrete
 *    - If any pure virtual function is not implemented, the class remains abstract
 *    - This ensures that any instantiable class provides complete implementation
 */

class Abstract {
public:
    virtual void mustImplement() = 0;
    virtual ~Abstract() {}
};

// This class doesn't implement mustImplement()
// So it remains abstract
class StillAbstract : public Abstract {
public:
    void someOtherFunction() {
        std::cout << "StillAbstract::someOtherFunction" << std::endl;
    }
};

// This class implements mustImplement()
// So it becomes concrete
class Concrete : public StillAbstract {
public:
    void mustImplement() override {
        std::cout << "Concrete::mustImplement" << std::endl;
    }
};

int main() {
    // Abstract a;  // Error: cannot instantiate abstract class
    // StillAbstract sa;  // Error: cannot instantiate abstract class
    Concrete c;  // OK: all pure virtual functions are implemented
    
    c.mustImplement();
    c.someOtherFunction();
    
    return 0;
} 