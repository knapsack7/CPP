#include <cstdlib>
#include <iostream>

int main(){
    std::unique_ptr<int> p{new int[5]{1,2,3,4,5}};
    // default deleter is delete and hence its 
    // behaviour is not undefined
    //p[0] = 10; // u cant access directly like this
    p.get()[0] = 10; // this will work
    // luckily we can pass int[] as template parameter
    // and then delete[] will be called
    // and subscript operator will be available
    std::unique_ptr<int[]> p2{new int[5]{1,2,3,4,5}};
    p2[0] = 20;
    std::cout<< p2[0] << std::endl;
    return 0;
}