#include <iostream>

/*
 * How members are inherited in different access specifiers:
 * 
 * 1. Public Inheritance:
 *    - public members of base -> public in derived
 *    - protected members of base -> protected in derived
 *    - private members of base -> not accessible in derived
 * 
 * 2. Protected Inheritance:
 *    - public members of base -> protected in derived
 *    - protected members of base -> protected in derived
 *    - private members of base -> not accessible in derived
 * 
 * 3. Private Inheritance:
 *    - public members of base -> private in derived
 *    - protected members of base -> private in derived
 *    - private members of base -> not accessible in derived
 * 
 * Note: Private members are always inherited (they exist in memory)
 * but are never accessible in the derived class, regardless of
 * inheritance type. This is to maintain proper object construction
 * and destruction chain.
 */

class Animal{
public:
    void eat(){
        std::cout << "Animal is eating" << std::endl;
    }
    void Run(){
        std::cout << "Animal is running" << std::endl;
    }
    void speak(){
        std::cout << "Animal is speaking" << std::endl;
    }
};

class Dog: public Animal{
    public:
    // hides the eat function of the base class for dog objects
    void eat(){
        std::cout << "Dog eating meat" << std::endl;
    }
    void speak(){
        std::cout << "Dog is barking" << std::endl;
    }
};

int main(){
    Dog d;
    d.eat();
    d.Run();
    d.speak();
    return 0;
}