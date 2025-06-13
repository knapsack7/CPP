#include <iostream>
#include "../smart_pointers/integer.h"


// the problem here is that initializer_list receives
// same type of elements, so we can't pass different types of elements
// to the function
template<typename T>
void print(std::initializer_list<T> list){
    for(const auto &item : list){
        std::cout << item << " ";
    }
    std::cout << std::endl;
}




void print(){
    std::cout << std::endl;
}

//template parameter pack

template<typename T, typename... params>
void print(T&& a, params&&... args){
    std::cout << a;
    if (sizeof...(args) > 0){
        std::cout << ",";
    }
    print(std::forward<params>(args)...);
}

int main(){

    //print({1,2,3,4,5});
    //print(1, 2.5, 3, "4");
    Integer val{1};
    print(0, val, Integer{2});
    return 0;
}