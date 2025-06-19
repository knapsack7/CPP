#include <any>
#include <iostream>
#include <string>
#include <vector>

/*
 * STD::ANY
 * A wrapper that can hold value of any arbitrary type in a type-safe way
 * Replacement for void*
 * Contains both the value & its type
 * The value is accessed through std::any_cast
 * May allocate memory on the heap
 * Throws exception of type std::bad_any_Cast on wrong type access
 */



struct  Number{
    int value; // data member to store the number
    Number(int num) : value(num) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number() : value(0) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Number(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number(const Number & other) : value(other.value) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number(Number && other) noexcept : value(other.value) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Number & operator=(const Number & other){
        std::cout<<__PRETTY_FUNCTION__ << std::endl;
        if (this == &other){
            return *this;
        }
        value = other.value;
        return *this;
    }
    Number & operator=(Number && other) noexcept{
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (this == &other){
            return *this;
        }
        value = other.value;
        return *this;
    }
    friend std::ostream & operator<<(std::ostream & os, const Number & num){
        os << num.value;
        return os;
    }
};

void basics(){
    std::any v1 = 5;
    v1 = "Hello";

    if (v1.has_value()){
        if (v1.type() == typeid(int)){
            std::cout << "v1 is an int" << std::endl;
        }
        else if (v1.type() == typeid(std::string)){
            std::cout << "v1 is a string" << std::endl;
        }
    }

}

int main(){
    using namespace std::literals;
    //std::any number(Number{5});

    auto n1 = std::make_any<Number>(10);

    n1.reset(); // destructor called for underlying object

    n1 = 5;

    //auto n2 = std::any_cast<int>(n1); // returns a copy[r-value] of the value

     //auto & n2 = std::any_cast<int>(n1); // since return r value u cant hold reference 

    auto &n2 = std::any_cast<int&>(n1); // returns a reference to the value

    n2 = 100; // modifying the value through the reference

    std::cout << std::any_cast<int>(n1) << std::endl;

    auto p = std::any_cast<int>(&n1); // returns a pointer to the value

    if (p) {
        *p = 500;
        std::cout << *p << std::endl;
    } else {
        std::cout << "n1 does not hold an int!" << std::endl;
    }

    *p = 200;
    std::cout << *p << std::endl;

    return 0;
}