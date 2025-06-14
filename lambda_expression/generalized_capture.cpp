#include <iostream>
#include <fstream>
using namespace std;

/*
 * generalized capture (C++14)
 * This feature allows creation of new variablesin the capture clause
 * The type of these variables is deduced from the type produced
 * by the expression
 * Consequently, these variables must always be initialized
 * if the initializer expression is a variable, the new variable
 * can have the same or different name
 * To creat a reference, you have to use operator & 
 * before the variable name
 *  [var=expression]](args)
 *  [&var=expression](args)
 */

int main(){
    int x{9};
    auto f = [y = x](int arg){
        return arg + y;
    };
    std::cout << f(5) << std::endl;

    // if u want to capture a reference
    // u have to use operator & before the variable name
    auto f2 = [&y = x](int arg){
        return arg + y;
    };

    std::cout << f2(9) << std::endl;


    std::ofstream out{"file.txt"};

    // ofstream object is not copyable
    // auto write = [&out](const std::string& str){
    //     out << str;
    // };
    // out is leaking since we wanted to 
    // use it inside lambda

    auto write = [out = std::move(out)](const std::string& str) mutable{
        out << str;
    };

    write("Hello, World!");

    out.close();
    
    return 0;
}