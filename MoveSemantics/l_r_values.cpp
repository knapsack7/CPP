#include<iostream>

using namespace std;

// returns r value
int add(int x, int y){
    return x+y;
}

// returns l value
int& transform(int &x){
    x *= x;
    return x;
}

void print(int &x){
    std::cout<< "Print(int&)" << std::endl;
}

void print(const int &x){
    std::cout<< "Print(const int&)" << std::endl;
}

void print(int &&x){
    std::cout<< "Print(int&&)" << std::endl;
}

int main(){
    // x, y and z are l values & 5, 10 and 8 are r values
    //int x = 5;
    int y = 10;
    int z = 8;

    // Expression returns r-value
    //int result = (x+y)*z;

    // Expression returns l-value
    //++x = 6;

    int &&r1 = 10;
    int &&r2 = add(3,2);

    //int x = 0;
    //int &&re = x; // error: cannot bind rvalue reference of type 'int&&' to lvalue of type 'int'

    //int &ref = transform(x);
    const int &ref2 = 3;

    int x = 10;
    print(x);
    print(3); // calls print(const int &) when r-value accepting print is not present
 
    print(3);  // calls r-vale functions in case of overloading


    return 0; 
}

/*
    l-value:
        - has a name
        - All variables are l-values
        - can be assigned values
        - some expressions return l-values
        - l-value persists beyond the expression
        - functions that return by reference return l-values
        - reference to l-value (called l-value reference)
    
    r-values: introduced in C++11
        - does not have a name
        - r-value is a temporary value
        - cannot be assigned values
        - some expressions return r-values
        - r-value does not persist beyond the expression
        - functions that return by value return r-values
        - reference to r-value (called r-value reference)

    R-VALUE REFERENCES
        - A reference created to a temporary
        - represents a temporary
        - created with && operator
        - cannot point to l-values (exception when l-value is a const)
        - r-value references always bind to temporaries
        - l-value references always bind to l-values

    int &&r1 = 10; // r-value reference
    int &&r2 = Add(x+y); // Add returns by value(temporary)
    int &&r3 = 7+2; // Expression returns a temporary
*/