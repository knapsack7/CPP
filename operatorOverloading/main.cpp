#include <iostream>
#include "integer.h"


Integer operator+(const Integer &a, const Integer &b){
    Integer temp;
    temp.SetValue(a.GetValue() + b.GetValue());
    return temp;
}

Integer operator+(int a, const Integer &b){
    Integer temp;
    temp.SetValue(a + b.GetValue());
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Integer &obj){
    os << obj.GetValue();
    return os;
}


std::istream& operator>>(std::istream& is, Integer &obj){
    int value;
    is >> value;
    *obj.m_pInt = value;
    return is;
}   


int main(){
    Integer a(1), b(3);
    Integer sum = a + b;
    std::cout << sum.GetValue() << std::endl;

    ++sum;
    std::cout << sum.GetValue() << std::endl;

    std::cout << (sum++).GetValue() << std::endl;

    std::cout << sum.GetValue() << std::endl;

    if (a == b){
        std::cout << "a is equal to b" << std::endl;
    } else {
        std::cout << "a is not equal to b" << std::endl;
    }

    Integer c;
    c = a; // assignment operator
    std::cout << c.GetValue() << std::endl;


    Integer sum1 = 9 + a; // a.operator+(5)
    std::cout << sum1.GetValue() << std::endl;


    // the below line will not work bz if the operator<< is not overloaded for Integer class
    std::cout<< sum1 << std::endl;

    operator<<(std::cout, sum1).operator<<(std::endl);    

    std::cin >> a;

    std::cout << a << std::endl;

    a();
    return 0;
}
