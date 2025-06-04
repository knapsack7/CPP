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

int Integer::GetValue() const{
    return *m_pInt;
}

void Integer::SetValue(int value){
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