#include "integer.h"
#include <iostream>

/*
 move() is always used with l-value references to make it an r-value.
*/

void print(Integer val){
}
int main(){
   /* Integer a(1);
    auto b{a}; // copy constructor
    auto c{static_cast<Integer &&>(a)}; // move constructor, but less readable
    auto d{std::move(a)}; // move constructor, more readable
    */

    Integer a(1);
    a.SetValue(3);
    print(std::move(a));
    a.SetValue(5); // `a` is moved and is no longer valid casue seg fault
    std::cout << a.GetValue() << std::endl; // seg fault because we are accessing a after it has been moved

    // so remember after you move from an object, you should not read from it because it is an unspecified
    // state but you can always reinitialise it and reuse it.

    // Other use of move is with those objects which are not copyable but movable. Example: FileStream, Threads,
    // unique_ptr, etc.
    return 0;
}