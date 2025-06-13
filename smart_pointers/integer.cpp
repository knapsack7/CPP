#include "integer.h"
#include <iostream>

Integer::Integer(){
    std::cout << "Integer()" << std::endl;
    m_pInt = new int(0);
}

Integer::Integer(int value){
    std::cout << "Integer(int)" << std::endl;
    m_pInt = new int(value);
}

Integer::Integer(const Integer &obj){
    std::cout << "Integer(const Integer&)" << std::endl;
    m_pInt = new int(*obj.m_pInt);
}

Integer::Integer(Integer &&obj) noexcept{
    std::cout << "Integer(Integer&&)" << std::endl;
    m_pInt = obj.m_pInt;
    obj.m_pInt = nullptr;
}

Integer& Integer::operator=(const Integer &obj){
    std::cout << "operator=(const Integer&)" << std::endl;
    if (this == &obj){
        return *this;
    }
    delete m_pInt; // ensure no memory leak
    m_pInt = new int(*obj.m_pInt);
    return *this;
}

Integer& Integer::operator=(Integer &&obj) noexcept{
    std::cout << "operator=(const Integer&&)" << std::endl;
    if (this == &obj){
        return *this;
    }
    delete m_pInt; // ensure no memory leak
    m_pInt = new int(*obj.m_pInt);
    obj.m_pInt = nullptr;
    return *this;
}


int Integer::GetValue() const{
    return *m_pInt;
}

void Integer::SetValue(int value){
    // to avoid seg fault, we need to check if m_pInt is not nullptr
    // if move is performed on object, m_pInt will be nullptr
    if (m_pInt == nullptr)
        m_pInt = new int{};
    *m_pInt = value;
}

// Integer Integer::operator+(const Integer &obj) const{
//     std::cout << "operator+(const Integer&)" << std::endl;
//     Integer temp;
//     *(temp.m_pInt)= *m_pInt + *(obj.m_pInt);
//     return temp;
// }

Integer& Integer::operator++(){
    std::cout << "operator++ pre-increment" << std::endl;
    ++(*m_pInt);
    return *this;
}

Integer Integer::operator++(int){
    std::cout<< "operator++ post-increment" << std::endl;
    Integer temp(*this);  // Create a copy of the current object
    ++(*m_pInt);         // Increment the current object
    return temp;         // Return the original copy
}

bool Integer::operator==(const Integer &obj) const{
    return *m_pInt == *(obj.m_pInt);
}

void Integer::operator()(){
    std::cout << "operator() called" << std::endl;
    std::cout << "Value: " << *m_pInt << std::endl;
}

Integer::~Integer(){
    std::cout << "~Integer()" << std::endl;
    delete m_pInt;
}

std::ostream& operator<<(std::ostream& os, const Integer &obj){
    os << "Integer: " << *obj.m_pInt;
    return os;
}