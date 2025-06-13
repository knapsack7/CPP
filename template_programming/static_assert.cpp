/*
 * Static Assertions
 * static_assert is a new kind of declaration for evaluating expressions
 * Accepts an expression and a user defined message
 * used for testing an expressiong at compile time
 * If the expression returns false, the compiler displays the specified
 * message and compilation fails
 */

#include <iostream>
#include <assert.h>

int main(){

    // this check happens at run time
    static_assert(sizeof(void*) == 8, "compile in 64-bit mode only");    

    // this check happens at run time
    if (sizeof(void *) != 8){
        std::cout << "This is not a 64 bit machine\n";
    } else{
        // alright, 64 bit machine
    }

    return 0;
}