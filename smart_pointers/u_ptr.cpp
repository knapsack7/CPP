#include "integer.h"
#include <iostream>


void display(Integer* p){
    if (p == nullptr){
        std::cout << "p is nullptr" << std::endl;
    }
    else{
        std::cout <<p->GetValue() << std::endl;
    }
}

Integer* getPointer(int value){
    Integer* p = new Integer{value};
    return p;
}

void store(std::unique_ptr<Integer> p){
    std::cout << "storing data into a file : " <<p->GetValue() << std::endl;
}

void operate(int value){
    // unique pointer does have explicit constructor
    // thats we cant use = operator to assign a value to it
    // we have to use {} to assign a value to it (direct initialization)
    std::unique_ptr<Integer> p{getPointer(value)}; 
    if (p == nullptr){
        //p = new Integer{value};
        p.reset(new Integer{value});
    }
    p->SetValue(100);
    display(p.get());
    // this will delete the underlying pointer and makes it nullptr
    p = nullptr;
    p.reset(new Integer{});
    *p = __LINE__; // the underlying pointer is assigned integral value of __LINE__
    display(p.get());
    store(std::move(p));
}


int main(){
    operate(5);
}