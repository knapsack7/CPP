#include <iostream>
#include "integer.h"

/*
operator<type>() is type conversion operator
It accets no arguments
and has no return type
*/


int main(){
    Integer a1{5};
    //Initialization
    Integer a2 = 5; // this will work as there is a constructor that 
    a1 = 7;
    int x = static_cast<int>(a1); // user defined type to primitive type
    return 0;  
}