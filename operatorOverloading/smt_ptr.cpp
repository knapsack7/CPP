#include "integer.h"
#include <iostream>
#include <memory>

class IntPtr{
    Integer *h_ptr;
public:
    IntPtr(Integer *ptr) : h_ptr(ptr) {
        std::cout << "IntPtr constructor called" << std::endl;
    }
    ~IntPtr() { 
        std::cout << "IntPtr destructor called" << std::endl;
        delete h_ptr; 
    }
    Integer* operator->() const { return h_ptr; }
    Integer& operator*() const { return *h_ptr; }
};

void process(std::unique_ptr<Integer> p){
    std::cout << "Process function called" << std::endl;
    std::cout << p->GetValue() << std::endl;
}

void createInteger(){
    std::unique_ptr<Integer> p(new Integer);
    p->SetValue(10);
    (*p).SetValue(20);
    process(std::move(p));
}

int main(){
    createInteger();
    return 0;
}