#include <iostream>
#include "integer.h"

int main(){
    Integer a1{5}; // expression invokes the parameterized constructor
    // so constructor helped implicit conversion from int to Integer

    //Integer a2 = "abc"; // this will not work as there is no constructor that 
    // accepts string in Integer class

    //Integer a3 = 5.5; // this will not work as there is no constructor that 
    // can convert double to Integer

    Integer a4 = 5.5f; // this will work as there is a constructor that 
    // can convert float to Integer

    a4 = 7;

    std::cout << a4.GetValue() << std::endl;
    return 0;
}