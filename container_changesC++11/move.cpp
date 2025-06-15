#include <iostream>
#include "../smart_pointers/integer.h"


int main(){
    std::vector<Integer> vInt;
    vInt.emplace_back(1);
    vInt.emplace_back(2);
    vInt.emplace_back(3);
    vInt.emplace_back(4);
    vInt.emplace_back(5);
    // here move constructor of Integer will be called
    // as move is preferred over copy constructor
    // if move constructor is noexcept by STL containers

    for(auto &i : vInt){
        std::cout << i << " ";
    }
    return 0;
}