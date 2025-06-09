#include <iostream>
using namespace std;

/*
 * Unions are a special type of class that allows you to store different types of data in the same memory location
 * 
 */

/*
 * Gives the ability to represent all the members in the same memory
 * Saves space
 * However, it has several disadvantages
 * no way to know which types it holds
 * nested types with non-default constructors deletes the default constructor of 
 * the union
 * cannt assign objects of user-defined types directly to a union member
 * user-defined types are not destroyed implicitly.
 * can not have a base class
 * you can not have virtual functions in unions
 */

// By default, the member of the union is public

union Test{
    int x;
    char ch;
    Test(): ch{'a'}{
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Test(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main(){
    Test t;
    std::cout << t.ch << std::endl;

    t.x = 1000;

    std::cout << t.ch << std::endl;
    return 0;
}