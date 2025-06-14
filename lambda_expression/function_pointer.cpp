#include <iostream>

/*
WHY FUNCTION POINTERS ARE LIMITED IN MODERN C++:

1. Performance Limitations:
   - Function pointers cannot be inlined by the compiler
   - They are invoked through their address, making them slower
   - The compiler cannot optimize these calls effectively
   - Example: In our code, 'comp(arr[j + 1], arr[j])' cannot be inlined

2. State Management Issues:
   - Function pointers can only point to global functions
   - They cannot maintain state between calls
   - They cannot access instance variables
   - They cannot be member functions (unless static)

3. Modern C++ Alternatives and Their Benefits:

   a) Lambda Expressions:
      - Can capture variables from their scope
      - Can maintain state
      - Can be inlined by the compiler
      - Example: [](int a, int b) { return a < b; }

   b) Function Objects (Functors):
      - Can maintain state through member variables
      - Can be inlined
      - Can be templated
      - Example: class Comparator { int state; bool operator()(int a, int b); };

   c) std::function:
      - Type-erased function wrapper
      - Can store any callable (function, lambda, member function)
      - More flexible than raw function pointers
      - Example: std::function<bool(int,int)> comp;

   d) Member Function Pointers:
      - Can point to class member functions
      - Can be used with objects
      - More type-safe than raw function pointers

4. Why Modern C++ Features are Better:
   - Better optimization opportunities
   - Ability to maintain state
   - More flexibility in what can be called
   - Better type safety
   - Support for capturing variables
   - Support for object-oriented programming
   - Better performance through inlining
*/

template<typename T>
using comparator = bool(*)(T, T);

template<typename T, int size>
void customSort(T (&arr)[size], comparator<T> comp) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (comp(arr[j + 1], arr[j])) {
                // Swap elements
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


/*
This is possible because in C++, when you declare an array with an initializer
list like int arr[]{64, 34, 25, 12, 22, 11, 90}, the size is part of the
array's type information. The compiler knows the exact size at compile time.
*/

// Function to print array
template<typename T, int size>
void printArray(T (&arr)[size]) {
    for (const auto& x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// Comparator functions
bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

int main() {
    // Declare and initialize array
    int arr[]{64, 34, 25, 12, 22, 11, 90};
    
    // print original array
    std::cout << "Original array: ";
    printArray(arr);
    
    // Sort in ascending order
    customSort(arr, ascending);
    std::cout << "Array after ascending sort: ";
    printArray(arr);
    
    // Sort in descending order
    customSort(arr, descending);
    std::cout << "Array after descending sort: ";
    printArray(arr);
    
    return 0;
}
