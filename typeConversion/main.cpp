#include <iostream>
using namespace std;

int main(){
    int a = 5, b = 2;
    // c style type conversion is discouraged in c++
    float f = static_cast<float>(a) / b;
    std::cout<<f<<std::endl;
    char *p = reinterpret_cast<char*>(&a); // reinterpret_cast is used to convert
    // one type to another unrelated type
    std::cout<<*p<<std::endl;

    const int x = 1;
    //int* p = reinterpret_cast<int*>(&x); // this will not allow as const
    // qualifier wont be supressed 
    std::cout<<*p<<std::endl;

    // const_cast is used to remove constness of a variable
    const int y = 2;
    int* q = const_cast<int*>(&y);
    std::cout<<*q<<std::endl;

    return 0;
}