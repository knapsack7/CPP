#include <iostream>
#include "integer.h"


Integer add(const Integer &a, const Integer &b){
    Integer temp;
    temp.SetValue(a.GetValue() + b.GetValue());
    return temp;
}

int main(){
    Integer a(1), b(3);
    a.SetValue(add(a,b).GetValue());
    return 0;
}