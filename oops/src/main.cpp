#include "../include/account.h"
#include <iostream>
#include "../include/savings.h"
#include "../include/checking.h"
#include "../include/transaction.h"
#include <typeinfo>


int main(){
    Savings acc("Bob", 100, 50);
    //transact(acc);
    // std::cout <<"Size of Account: " << sizeof(Account) << std::endl; // 4 bytes for vtable pointer
    
    try{
        transact(acc);
    }catch(const std::exception &e){
        std::cout<< "Error: " << e.what() << std::endl;
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