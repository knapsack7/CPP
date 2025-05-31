#include <iostream>

// Base class
class Animal {
public:
    Animal() { std::cout << "Animal constructor\n"; }
    ~Animal() { std::cout << "Animal destructor\n"; }
};

// Intermediate classes
// virtual public Animal means:
// 1. virtual: This class will share a single instance of Animal with other classes
//    that also virtually inherit from Animal
// 2. This prevents the "diamond problem" where multiple copies of Animal would exist
// 3. The most derived class (Bat) will be responsible for initializing the virtual base
class Mammal : virtual public Animal {
public:
    Mammal() { std::cout << "Mammal constructor\n"; }
    ~Mammal() { std::cout << "Mammal destructor\n"; }
};

// Same virtual inheritance here
// Both Mammal and Bird will share the same Animal instance
// Without virtual, Bat would have two separate Animal instances
class Bird : virtual public Animal {
public:
    Bird() { std::cout << "Bird constructor\n"; }
    ~Bird() { std::cout << "Bird destructor\n"; }
};

// Member class
class Feature {
public:
    Feature() { std::cout << "Feature constructor\n"; }
    ~Feature() { std::cout << "Feature destructor\n"; }
};

// Bat inherits from both Mammal and Bird
// Because of virtual inheritance, Bat will have only one Animal instance
// The inheritance hierarchy looks like this:
//        Animal
//        /    \
//    Mammal   Bird
//        \    /
//         Bat
class Bat : public Mammal, public Bird {
    Feature feature;  // Member object
public:
    Bat() {
        std::cout << "Bat constructor body\n";
    }
    ~Bat() {
        std::cout << "Bat destructor\n";
    }
};

int main() {
    Bat bat;
    return 0;
}