#include<iostream>

/*
Learning you must use the scope resolution operator to call static
members of classes
*/

class ClassG {
public:
    static int get_x() { return x;}
    static int x;
};

int ClassG::x = 6;

int main(){
    int gx1 = ClassG::x;
    int gx2 = ClassG::get_x();
    std::cout<<gx1<<"---"<<gx2<<std::endl;
}