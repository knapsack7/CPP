#include "integer.h"
#include <iostream>

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

int main(){
    IntPtr ptr = new Integer;
    ptr->SetValue(10);
    (*ptr).SetValue(30);
    std::cout << ptr->GetValue() << std::endl;
    std::cout << "About to return from main" << std::endl;
    return 0;
}