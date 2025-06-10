/*
 * noexcept is a specifier that tells the compiler that a function
 * will not throw an exception.
 * applied to functions(both in declaration and definition) 
 * indicates the function does not throw an exception
 * Compiler can optimize the function code
 *       no need to generate stack unwinding code
 * An exception thrown from a noexcept function will terminate the program
 *       stack may or may not be unwinded. If stack not not unwinded, the destructor wont be
 *       called and heap memory leakage may happen.
 * Not all functions should use noexcept specifier.
 *      specially functions calling other functions (in library)
 *      such functions will be exception-neutral
 */

#include <iostream>

// noexcept(true) means the function will not throw an exception
// noexcept(false) means the function may throw an exception
// noexcept(noexcept(expression)) means the function will not throw an exception
//       if the expression is true, otherwise it may throw an exception

// ALWAYS REMEBER: NoEXCEPT function may thow an exception 
// as they may call other functions that may throw an exception

// by default, this may throw an exception
void test(int x) noexcept(false){
    std::cout << x << std::endl;
    throw x;
}

int sum(int x, int y) noexcept(noexcept(test(x))) {
    test(x);
    return x + y;
}

class A{
public:
   
    ~A(){
        std::cout << "~A()" << std::endl;
    }
};

/*
 * Why mark move operations as noexcept?
 * 1. Container Optimization: Allows vectors/containers to use move instead of copy during reallocation
 * 2. Performance: Enables efficient memory management without exception handling overhead
 * 3. Exception Safety: Guarantees move won't leave objects in invalid state
 * 4. Standard Library: Required for proper interaction with STL containers
 * 
 * Best Practice: Always mark move operations as noexcept unless they must throw
 */

int main(){
    A a;
    // destructor prints true, that mean in c++ all destructors are noexcept
    std::cout << std::boolalpha<< noexcept(a.~A()) << std::endl;
    try{
        sum(10, 20);
    } catch (int x){
        std::cout<< x << std::endl;
    }
    return 0;
}