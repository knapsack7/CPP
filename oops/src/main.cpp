#include "../include/account.h"
#include <iostream>
#include "../include/savings.h"
#include "../include/checking.h"
#include "../include/transaction.h"
#include <typeinfo>
#include <cxxabi.h>


// Function to demangle type names
std::string demangle(const char* mangled_name) {
    int status;
    char* demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    if (status == 0) {
        std::string result(demangled);
        free(demangled);
        return result;
    }
    return mangled_name;
}

int main(){
    Checking acc("Bob", 100, 50);
    Account *p = &acc;
    // transact(&acc);
    // std::cout <<"Size of Account: " << sizeof(Account) << std::endl; // 4 bytes for vtable pointer
    
    int i{};

    float f{};
    const std::type_info &ti = typeid(acc);

    if (typeid(acc) == typeid(Checking)){
        std::cout<< "acc is a Checking object" << std::endl;
    }
    else{
        std::cout<< "acc is not a Checking object" << std::endl;
    }
    
    return 0;
}

/*
 * typeid behavior:
 * 1. Compile-time evaluation:
 *    - When used with non-polymorphic types
 *    - When used with type names directly (not objects)
 *    - When used with built-in types
 *    Example: typeid(int), typeid(std::string)
 * 
 * 2. Runtime evaluation:
 *    - When used with polymorphic types (classes with virtual functions)
 *    - When used with objects of derived classes through base pointers
 *    - When used with dynamic_cast
 *    Example: typeid(*ptr) where ptr is a base class pointer
 */