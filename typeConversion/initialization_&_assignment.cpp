#include <iostream>
#include "integer.h"

class Product{
    Integer m_Id;
public:
    // Member initialisor initializes the member variable in order in which
    // they are declared in the class
    // always try to use member initialisor instead of assignment operator
    Product(const Integer &id) : m_Id(id) {
        // m_Id = id; // this will call the assignment operator try to avoid this
        std::cout << "Product(const Integer &)called" << std::endl;
    }
    ~Product(){
        std::cout << "~Product() called" << std::endl;
    }
};

int main(){
    Product p(5);

    // Assignment makes more constructor calls than initialization 
    // so use initialization when ever possible
    return 0;
}