/*
Liskov Substitution Principle (LSP) in C++

📌 Principle Definition:

	Subtypes must be substitutable for their base types without altering the correctness of the program.

This means that if a class B is a subclass of A, 
then B should be usable wherever A is expected without breaking functionality.

*/

/*
🚨 Violation of LSP (Bad Example)

Here, we create a Bird base class with a fly() method, but we also have a Penguin subclass.
Since penguins cannot fly, overriding fly() leads to incorrect behavior.
*/
#include <iostream>
using namespace std;

// ❌ BAD: Base class assumes all birds can fly
class Bird {
public:
    virtual void fly() {
        cout << "Bird is flying." << endl;
    }
};

// ✅ Sparrow can fly, so it works fine
class Sparrow : public Bird {
public:
    void fly() override {
        cout << "Sparrow is flying." << endl;
    }
};

// ❌ Problem: Penguins cannot fly, but are forced to implement fly()
class Penguin : public Bird {
public:
    void fly() override {
        throw logic_error("Penguins cannot fly!"); // ❌ Runtime error
    }
};

// Function expecting a Bird but breaking for Penguins
// Here for the subtype Penguin Base class Bird is not substitutabel with it 
// as Penguin dont fly and it will throw an error
void makeBirdFly(Bird* bird) {
    bird->fly();  // ❌ Throws error for Penguin
}

int main() {
    Sparrow sparrow;
    makeBirdFly(&sparrow);  // ✅ Works fine

    Penguin penguin;
    makeBirdFly(&penguin);  // ❌ Breaks LSP

    return 0;
}

/*

🔴 Problems in this approach:
	1.	Breaks LSP – Penguin cannot behave as a Bird because fly() is invalid.
	2.	Unexpected runtime errors – Calling fly() on a Penguin results in an exception.
	3.	Violates OCP (Open/Closed Principle) – Every time we add a non-flying bird, 
    we must modify the base class or check conditions manually.
*/