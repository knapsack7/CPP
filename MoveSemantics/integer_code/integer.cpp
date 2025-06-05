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

Integer::~Integer(){
    std::cout << "~Integer()" << std::endl;
    delete m_pInt;
}

/*
The reason you are not seeing "Integer(Integer&&)" 
(the move constructor print statement) is because of copy elision 
(specifically, Return Value Optimization, or RVO).
Use this flag during compilation to avoid optimisation.
-fno-elide-constructors
*/