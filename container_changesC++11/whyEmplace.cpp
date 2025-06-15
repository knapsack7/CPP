#include "../smart_pointers/integer.h"
#include <iostream>


int main(){
    std::vector<Integer> vInt;
    // this will first call paramterised constructor of Integer
    // and then move constructor of Integer
    vInt.push_back(10);

    // this will first call paramterised constructor of Integer
    // and no/copy construcor
    vInt.emplace_back(10);

    std::vector<std::pair<int, std::string>> vPair;

    vPair.push_back(std::make_pair(10, "Hello"));

    vPair.emplace_back(10, "Hello");
    
    return 0;
}