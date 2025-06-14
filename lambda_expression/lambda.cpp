#include <iostream>

/*
 * LAMBDA EXPRESSION
 * Typically, encapsulates a few lines of code
 * behaves like a normal fucntion when invoked
 * replaces function objects
 * Internally, implemented as a nameless function object
 * Use auto to provide an explicit name
 */

struct Unnamed{
    int operator()(int x, int y) const{
        return x + y;
    }
};
int main(){
    [](){
        std::cout << "Hello, World!" << std::endl;
    }();

    auto fn = [](){
        std::cout << "Hello, God!" << std::endl;
    };

    fn();

    std::cout<< typeid(fn).name() << std::endl;

    // if the lambda meant to be return void or same type as its argument then there
    // is no need to mention its return type
    // auto sum = [](int a, int b) -> double{
    //     if (a > b){
    //         return 5.2;
    //     }else
    //         return a;
    // };

    // Note: lamda expression internally represents as a
    // function object

    auto sum = [](int a, int b){
        return a + b;
    };

    std::cout << sum(10, 5) << std::endl;

    // Note: lamda expression internally represents as a
    // function object


    Unnamed n;

    std::cout << n(10, 78) << std::endl;


    // Generic lambda expression that can accept any type of argument
    // C++14 onwards
    auto multiply = [](auto a, auto b)noexcept(false){
        return a * b;
    };

    std::cout << multiply(10, 5.4) << std::endl;
    
    
    return 0;
}