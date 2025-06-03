#include <iostream>
#include <vector>
#include <string>
#include <utility>  // for std::move and std::forward

using namespace std;

// Example class for move semantics
class Resource {
private:
    vector<int> data;
    string name;

public:
    Resource(string n) : name(n) {
        cout << "Resource " << name << " constructed" << endl;
    }

    // Move constructor
    Resource(Resource&& other) noexcept 
        : data(std::move(other.data)), name(std::move(other.name)) {
        cout << "Resource " << name << " moved" << endl;
    }

    // Move assignment operator
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            name = std::move(other.name);
            cout << "Resource " << name << " move assigned" << endl;
        }
        return *this;
    }

    ~Resource() {
        cout << "Resource " << name << " destroyed" << endl;
    }
};

// Function demonstrating perfect forwarding
template<typename T>
void processValue(T&& value) {
    cout << "Processing value: " << value << endl;
}

// Function taking const reference
void processConstRef(const int& value) {
    cout << "Processing const reference: " << value << endl;
}

// Function taking r-value reference
void processRValueRef(int&& value) {
    cout << "Processing r-value reference: " << value << endl;
}

// Function taking l-value reference
void processLValueRef(int& value) {
    cout << "Processing l-value reference: " << value << endl;
}

int main() {
    cout << "=== Basic Reference Binding Examples ===" << endl;
    
    int x = 10;  // l-value
    
    // L-value references
    int& lref1 = x;     // OK: l-value reference to l-value
    // int& lref2 = 10;  // Error: l-value reference cannot bind to r-value
    const int& lref3 = 10;  // OK: const l-value reference can bind to r-value
    
    cout << "lref1: " << lref1 << endl;
    cout << "lref3: " << lref3 << endl;
    
    // R-value references
    int&& rref1 = 10;    // OK: r-value reference to r-value
    int&& rref2 = std::move(x);  // OK: r-value reference to moved l-value
    // int&& rref3 = x;  // Error: r-value reference cannot bind to l-value directly
    
    cout << "rref1: " << rref1 << endl;
    cout << "rref2: " << rref2 << endl;
    
    cout << "\n=== Function Call Examples ===" << endl;
    
    // Function calls with different reference types
    processLValueRef(x);     // OK: l-value
    // processLValueRef(10);  // Error: cannot bind l-value reference to r-value
    
    processRValueRef(10);    // OK: r-value
    processRValueRef(std::move(x));  // OK: moved l-value
    
    processConstRef(x);      // OK: l-value
    processConstRef(10);     // OK: r-value
    
    cout << "\n=== Perfect Forwarding Example ===" << endl;
    
    // Universal reference (perfect forwarding)
    processValue(x);     // OK: l-value
    processValue(10);    // OK: r-value
    
    cout << "\n=== Move Semantics Example ===" << endl;
    
    // Move semantics demonstration
    Resource r1("Resource1");
    Resource r2("Resource2");
    
    cout << "Moving r1 to r2..." << endl;
    r2 = std::move(r1);  // Move assignment
    
    Resource r3(std::move(r2));  // Move construction
    
    cout << "\n=== Universal Reference Example ===" << endl;
    
    // Universal references with auto
    auto&& uref1 = x;    // OK: binds to l-value
    auto&& uref2 = 10;   // OK: binds to r-value
    
    cout << "uref1: " << uref1 << endl;
    cout << "uref2: " << uref2 << endl;
    
    return 0;
} 