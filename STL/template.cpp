// Points:
// 1. There are two places where we can apply templates
//     a. function templates
//     b. class templates
// 2. Templates are the way to write generic programs.
// 3. The main point is we pass data type as parameter to function or class.


#include <iostream>
using namespace std;

template<typename T>
T getMax(T a, T b){
    if (a > b)
        return a;
    else
        return b;
}

int main() {
    cout<<getMax<int>(1,2)<<endl;
    char c1 = 'a', c2 = 'c';
    cout<<getMax<char>(c1,c2)<<endl;
    return 0;
}