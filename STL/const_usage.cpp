#include <iostream>
#include <string>
#include <set>
using namespace std;


/*

Usage                         Meaning
const int x                   x is read-only
int* const p                  pointer is const [say, p is a constant pointer to int [read right to left]]
const int* p                  pointee is const [say, p is a pointer to a constant int[read right to left]]


int x = 10, y = 20;

// 1️⃣ Value constant
const int* p1 = &x;
p1 = &y;      // ✅ allowed
*p1 = 100;    // ❌ not allowed

// 2️⃣ Pointer constant
int* const p2 = &x;
*p2 = 100;    // ✅ allowed
p2 = &y;      // ❌ not allowed

// 3️⃣ Both constant
const int* const p3 = &x;
*p3 = 100;    // ❌ not allowed
p3 = &y;      // ❌ not allowed


const int* const p            both are const
const T& or const T* param    pass-by-ref/pointer without allowing modification
void func() const             member function won't modify object
const T get()                 returned object can't be assigned
const T& get()                return a reference, but caller can't modify it
mutable                       member can be modified in const function
*/

class Person {
private:
    const int id;                  // const data member (must be initialized)
    string name;
    mutable int accessCount = 0;   // mutable allows change in const functions

public:
    Person(int id, const string& name) : id(id), name(name) {}

    // Const member function - won't modify 'this'
    string getName() const {
        accessCount++;  // allowed because accessCount is mutable
        return name;
    }

    // Non-const member function
    void setName(const string& newName) {
        name = newName;
    }

    // Const return by reference
    const string& getNameRef() const {
        return name;
    }

    // Operator< with const correctness
    bool operator<(const Person& other) const {
        return id < other.id;
    }

    // Display function
    void print() const {
        cout << "ID: " << id << ", Name: " << name
             << ", Accessed: " << accessCount << " times\n";
    }
};

// Function that takes a const reference
void displayPerson(const Person& p) {
    cout << "Person: " << p.getName() << endl;
}

int main() {
    // const variable
    const int maxPersons = 3;

    // const pointer and pointee
    int age = 30;
    const int* ptrToConst = &age; // *ptrToConst is const
    int* const constPtr = &age;   // constPtr cannot point elsewhere
    const int* const constPtrToConst = &age; // both const

    // Using set with const correctness and operator<
    set<Person> people = {
        Person(2, "Alice"),
        Person(1, "Bob"),
        Person(3, "Charlie")
    };

    for (const auto& person : people) {  // const reference to prevent modification
        displayPerson(person);
    }

    cout << "\nUpdating name for ID 2...\n";
    for (auto& person : people) {
        if (person.getName() == "Alice") {
            // ❌ Not allowed to modify because set elements are const
            // person.setName("Alicia"); // <-- this would be an error
        }
    }

    // Using mutable: print how many times name was accessed
    cout << "\nAccess summary:\n";
    for (const auto& person : people) {
        person.print();
    }

    return 0;
}