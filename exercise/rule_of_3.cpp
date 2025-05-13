#include <iostream>
#include <vector>
using namespace std;
/*
 * ✨ Bonus Tip – Rule of Three:
If your class allocates resources (like dynamic memory):

You should define:

Copy Constructor

Copy Assignment Operator

Destructor

Because shallow copies will otherwise lead to double delete, memory corruption, or shared state bugs✨ Bonus Tip – Rule of Three:
If your class allocates resources (like dynamic memory):

You should define:

Copy Constructor

Copy Assignment Operator

Destructor

Because shallow copies will otherwise lead to double delete, memory corruption, or shared state bugs
 */

class Data {
    int* ptr;

public:
    Data(int val) {
        ptr = new int(val);
        cout << "Constructor: ptr = " << ptr << ", value = " << *ptr << endl;
    }

    // Deep copy constructor
    Data(const Data& other) {
        ptr = new int(*other.ptr);
        cout << "Copy Constructor: new ptr = " << ptr << ", copied value = " << *ptr << endl;
    }

    // Deep copy assignment
    Data& operator=(const Data& other) {
        if (this != &other) {
            delete ptr;
            ptr = new int(*other.ptr);
            cout << "Assignment: new ptr = " << ptr << ", copied value = " << *ptr << endl;
        }
        return *this;
    }

    // Destructor
    ~Data() {
        cout << "Destructor: deleting ptr = " << ptr << endl;
        delete ptr;
    }

    void show() {
        cout << "ptr = " << ptr << ", value = " << *ptr << endl;
    }

    void update(){
        *(this->ptr) = 99;
    }
};


int main() {
    Data d1(10);
    Data d2 = d1; // Deep copy - new memory!

    cout << "Before modifying d2:" << endl;
    d1.show();
    d2.show();

    d1.update();

    cout << "After modifying d2:" << endl;
    d1.show(); // Unaffected
    d2.show(); // Updated

    return 0;
}
