#include <iostream>
#include <type_traits>

/*
 * Type Traits [works at compile time]
 * Type traits give the ability to introspect
 *     find the characteristics of types at compile time
 *     transform the properties of the type
 * Useful in template programming
 * Will either return a boolean or a type when inspecting types
 * provides template-based interface and defined in header <type_traits>
 * Some traits require support from the compiler
 *     compiler provides intrinsics for such traits
 */


template<typename T>
T divide(T a, T b){
    if (std::is_floating_point<T>::value == false){
        std::cout << "Use floating point types only\n";
        return 0;
    }
    return a/b;
}

template<typename T>
void check(T &&){
    std::cout<< std::boolalpha;
    std::cout<< "Is reference ?" << std::is_reference<T>::value<<std::endl;

    std::cout << "After Removing:" <<
    std::is_reference<typename std::remove_reference<T>::type>::value<<std::endl;
}

int main(){

    check(5);
    int value{13};
    check(value);

    // std::cout<<std::boolalpha<<"Is integer ?" << std::is_integral<int>::value<<std::endl;
    // std::cout<<divide(5, 2)<<std::endl;
    return 0;
}