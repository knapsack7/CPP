#include<iostream>
#include<memory>
using namespace std;

/*
C++11 introduced move semantics to optimize performance when dealing with temporary objects or large resources (like dynamic memory, file handles, sockets, etc.).

So, if your class:

Manages resources manually (like raw pointers, file descriptors),

You should implement not just:

Copy constructor,

Copy assignment,

Destructor
But also:

Move constructor,

Move assignment operator

➡️ These 5 make up the Rule of Five.

⚠️ What Problem Does It Solve?
Consider this code:

Data d1(100);
Data d2 = std::move(d1); // Move constructor should be called here

If you don’t implement a move constructor, this will fall back to copy constructor, which may be expensive or unsafe.

*/

#include <iostream>
using namespace std;

class Data {
    int* ptr;

public:
    // Constructor
    Data(int val) {
        ptr = new int(val);
        cout << "Constructor: " << ptr << " -> " << *ptr << endl;
    }

    // Copy constructor (deep copy)
    Data(const Data& other) {
        ptr = new int(*other.ptr);
        cout << "Copy Constructor: " << ptr << " -> " << *ptr << endl;
    }

    // Copy assignment (deep copy)
    /*
    In C++, assignment operators overwrite the existing contents of an object. So before copying or moving new data into the object, you must clean up the old data to prevent:

    Memory leaks (you lose access to the old ptr memory)

    Dangling pointers or resource duplication
    */

    Data& operator=(const Data& other) {
        if (this != &other) {
            delete ptr; // 🧹 clean up current resource memory allocated by constructor so need to delete as it may
            // cause danglin pointer issue
            ptr = new int(*other.ptr);
            cout << "Copy Assignment: " << ptr << " -> " << *ptr << endl;
        }
        return *this;
    }

    // Move constructor (steal the pointer)
    Data(Data&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
        cout << "Move Constructor: " << ptr << endl;
    }

    // Move assignment (steal the pointer). Only Pointers are stolen memory on the heap is as it was.
    // Heap Memory is  not moved or copied - only the pointer is reassigned 
    Data& operator=(Data&& other) noexcept {
        if (this != &other) {
            delete ptr; // 🧹 clean up current resource memory allocated by constructor so need to delete as it may
            // cause danglin pointer issue
            ptr = other.ptr; //take ownership
            other.ptr = nullptr; // avoid double delete. After assignment, other.ptr is nulled
            // so that its destructor won’t delete it again (preventing double free).
            cout << "Move Assignment: " << ptr << endl;
        }
        return *this;
    }

    // Destructor
    ~Data() {
        cout << "Destructor: deleting " << ptr << endl;
        delete ptr;
    }

    void show() const {
        if (ptr)
            cout << "Value: " << *ptr << " at " << ptr << endl;
        else
            cout << "Null ptr" << endl;
    }
};

int main() {
    Data d1(10);
    Data d2 = std::move(d1); // Calls move constructor
    d2.show();
    d1.show();               // Should show null

    Data d3(20);
    d3 = std::move(d2);      // Calls move assignment
    d3.show();
}


/*
🚀 Benefits of Move Semantics:
Avoids expensive deep copies.

Improves performance especially when returning large objects from functions.

Essential in container classes like std::vector, std::map. Also for multithreading.

❗ When to Use Rule of Five?
Use Rule of Five if:

Your class manages resources (memory, file handles, etc.).

You need performance and want to avoid unnecessary copies.

If your class doesn't manage any such resource, 
you don't need to define any of the five — compiler-generated versions are enough (Rule of Zero).

*/