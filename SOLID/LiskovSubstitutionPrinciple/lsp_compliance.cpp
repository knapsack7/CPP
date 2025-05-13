/*
✅ Correct Approach (Compliant with LSP)

We separate flying and non-flying birds into different classes,
ensuring each class follows the expected behavior.
*/
#include <iostream>
#include <memory>  // For smart pointers
using namespace std;

// ✅ Define a base Bird class (without forcing fly behavior)
class Bird {
public:
    virtual void makeSound() {
        cout << "Bird is chirping." << endl;
    }
    virtual ~Bird() {}  // Must Virtual destructor for proper cleanup
};

// ✅ Separate interface for flying birds
class IFlyable {
public:
    virtual void fly() = 0;
    virtual ~IFlyable() {}
};

// ✅ Sparrow is a Bird and can fly
class Sparrow : public Bird, public IFlyable {
public:
    void fly() override {
        cout << "Sparrow is flying." << endl;
    }
};

// ✅ Penguin is a Bird but NOT Flyable
class Penguin : public Bird {
public:
    void makeSound() override {
        cout << "Penguin is squawking." << endl;
    }
};

// ✅ Function that works only for flying birds
// see Bird base class is changed with the IFlyable Interface
void makeBirdFly(IFlyable* bird) {
    bird->fly();  // ✅ Now only flyable birds can be passed
}

int main() {
    // Using smart pointers for automatic memory management
    unique_ptr<Sparrow> sparrow = make_unique<Sparrow>();
    makeBirdFly(sparrow.get());  // ✅ Works fine

    unique_ptr<Penguin> penguin = make_unique<Penguin>();
    penguin->makeSound();  // ✅ Works fine

    // makeBirdFly(penguin);  // ❌ Compile-time error prevents incorrect behavior

    return 0;
}

/*

🔥 Key Benefits of Using LSP

✅ Prevents incorrect assumptions – No non-flying bird is forced to implement fly().
✅ Ensures substitutability – Every subclass can be used without unexpected behavior.
✅ Better maintainability – New bird types can be added without modifying existing code.

✅ Memory Safety: std::unique_ptr ensures automatic deallocation (no memory leaks).
✅ Prevents Incorrect Usage: We cannot pass Penguin to makeBirdFly(), enforcing LSP at compile time.
✅ Proper Object Substitution: Sparrow can be used anywhere IFlyable is expected without issues.
✅ Scalability: Adding new birds (e.g., Eagle, Ostrich) doesn’t require modifying existing code.

*/