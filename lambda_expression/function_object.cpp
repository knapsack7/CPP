#include <iostream>


/*
FUNCTION OBJECTS (FUNCTORS) IN C++:

1. What is a Function Object?
   - A class that overloads the operator()
   - Can be called like a function
   - Can maintain state between calls
   - Can be inlined by the compiler
   - More flexible than function pointers

2. Advantages over Function Pointers:
   - Can maintain state through member variables
   - Can be inlined by the compiler
   - Can be templated
   - Can have multiple overloaded operator() methods
   - Can have constructors and destructors
   - Can have other member functions

3. Common Use Cases:
   - Custom sorting criteria
   - Stateful predicates
   - Configurable behavior
   - Callback mechanisms

4. Key Benefits:
   - Better performance (can be inlined)
   - State management
   - Object-oriented features
   - Type safety
   - Flexibility in implementation
   - Can be used with STL algorithms
*/


/*
WHY CALLBACKS (FUNCTION OBJECTS) ARE BETTER THAN FUNCTION POINTERS:

1. Performance Benefits:
   - Function objects can be inlined by the compiler, leading to better performance
   - Function pointers cannot be inlined as they are resolved at runtime
   - This makes function objects significantly faster in tight loops and performance-critical code

2. State Management:
   - Function objects can maintain state through member variables
   - Function pointers are stateless and cannot store data between calls
   - This allows for more complex and flexible callback implementations
   - Example: A counter function object can keep track of how many times it's been called
   - Example: A function object can remember previous values and use them in future calls
   - Example: A function object can maintain configuration settings throughout its lifetime
   - This state persistence is impossible with function pointers, which are just addresses to functions

3. Type Safety:
   - Function objects provide better type checking at compile time
   - Function pointers can lead to type mismatches that are only caught at runtime
   - Templates with function objects ensure type safety across different data types

4. Object-Oriented Features:
   - Function objects can have constructors, destructors, and other member functions
   - They can inherit from other classes and implement interfaces
   - This enables better code organization and reuse

5. Flexibility:
   - Function objects can have multiple overloaded operator() methods
   - They can be templated to work with different types
   - They can be used with STL algorithms and containers
   - Function pointers are limited to a single function signature

6. Modern C++ Integration:
   - Function objects work seamlessly with modern C++ features like lambdas
   - They can be used with std::function, which provides type erasure
   - They integrate well with the STL and other modern C++ libraries

7. Debugging and Maintenance:
   - Function objects are easier to debug as they can have meaningful names and types
   - They can be extended with additional functionality without changing the interface
   - Function pointers are harder to debug and maintain due to their opaque nature
*/


template<typename T>
class Functor{

public:
    Functor() = default;

    bool operator()(T a, T b) const{
        return a < b;
    }
};

template<typename T, int size>
void customSort(T (&arr)[size], Functor<T> comp) {
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


int main() {
    
    Functor<int> comp;
    comp(3,4); // comp.operator()(3,4)
    
     // Declare and initialize array
    int arr[]{64, 34, 25, 12, 22, 11, 90};
    
    // print original array
    std::cout << "Original array: ";
    printArray(arr);
    
    // Sort in ascending order
    customSort(arr, comp);
    std::cout << "Array after ascending sort: ";
    printArray(arr);
    
    // Sort in descending order
    customSort(arr, comp);
    std::cout << "Array after descending sort: ";
    printArray(arr);
    


    return 0;
}
