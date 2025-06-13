#include <iostream>
#include <string>
#include <cxxabi.h>

// Helper function to demangle type names
std::string demangle(const char* mangled) {
    int status;
    char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
    if (status == 0) {
        std::string result(demangled);
        free(demangled);
        return result;
    }
    return mangled;
}


// non-type template argument must be a constant expression
// which can be evaluated at compile time


// template<typename T>
// T sum(T* arr, int size){
//     T sum{};
//     for(int i = 0; i < size; ++i){
//         sum += arr[i];
//     }
//     return sum;
// }


// so using reference to an array and non-type template arguments,
// we can pass an into a function without explicitly passing the size
// This is used by the standard library to implement the global functions,
// std::begin() and std::end()
template<typename T, int size>
T sum(T (&parr) [size]){
    T sum{};
    for(int i = 0; i < size; ++i){
        sum += parr[i];
    }
    return sum;
}

template<int size>
void print(){
    char buffer[size];
    std::cout << "size: " << size << std::endl;
}

/*
 * Non - Type Template Arguments
 * Expression that is computed at compile time within a template argument list
 * Must be a constant expression(addresses, references, integrals, nullptr, enums)
 * Part of the template type
 * Used by std::begin() and std::end() functions
 */

int main(){
   int arr[]{3,1,4,3};

   //int agg = sum(arr, 4);

   // so using reference to an array and non-type template arguments,
    // we can pass an into a function without explicitly passing the size

   int agg = sum(arr);
   std::cout << "sum: " << agg << std::endl;
    
    return 0;   
}