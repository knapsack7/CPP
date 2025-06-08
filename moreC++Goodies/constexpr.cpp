#include <iostream>
using namespace std;

/*
 * constexpr is a keyword that allows you to define a constant expression
 * which allows the compiler to evaluate the expression at compile time
 * 
 */


constexpr int GetNumber(){
    return 42;
}

constexpr int Add(int x, int y){
    return x+y;
}

constexpr int Max(int x, int y){
    return x > y ? x : y; // must be a single line statement below c++14
}

int main(){

    // behaves as a constant expression function
    constexpr int num = GetNumber();
    cout << num << endl;


    // behaves as a constant expression function
    const int j = GetNumber();
    int arr1[j];

    /*The key difference is that constexpr functions can be 
    evaluated at both compile time and runtime. When you use 
    the result in a context that requires a compile-time 
    constant (like array size or constexpr variable),
    it's evaluated at compile time. When you use it in a normal 
    variable, it's evaluated at runtime
    */    

    // Behaves as a normal function call
    int x = GetNumber();

    constexpr int sum = Add(1,2);
    cout << sum << endl;
    return 0;
}

// constant expression functions rules

// should accept and return literal types only
// void, scalar types(int, float, char), references, etc...
// should contain only single line statement that should be a return statement below c++14

// constant expression functions are implicitly inline
// this means that u have to write constant expr just like an inline function.
// so constexpr functions will always be defined in the header file


// Const Vs Constexpr
// Initialization of a const variable can be deferred until runtime
// However, a constantexpr variables must be initialized at compile time
// all constexpr variables are const, but not the other way around
// Use const keyword to indicate the value cannt be modified.
// Use constexpr to create expressions that can be evaluated at compile time
// const is used to declare variables that cannot be modified after initialization