#include <iostream>
#include "integer.h"


Integer operator+(const Integer &a, const Integer &b){
    Integer temp;
    temp.SetValue(a.GetValue() + b.GetValue());
    return temp;
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

    return 0;
}
