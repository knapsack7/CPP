#include "integer.h"
#include <iostream>

class Number{
    Integer m_value{};
public:
    Number(int value): m_value(value){}

    Number(const Number &obj): m_value(obj.m_value){}
    
    // if you provide any custom function from the rule of 5, The synthesis of move constructor 
    // and move assignment operator is prevented. Use default specifier for move constructor 
    // and move assignment operator.
    ~Number(){
        std::cout << "~Number()" << std::endl;
    }
    // if you provide custom implementation of any move functions, the copy constructor and copy assignment operator's
    // synthesis is also prevented.

    // Thats why it is recommended to implement Rule of Five. If u provide any custom function
    // from the rule of 5. OR use default specifier for move constructor and move assignment operator. default is also
    // considered as custom implementation.
    Number(Number &&obj) noexcept: m_value(std::move(obj.m_value)){}
    Number& operator=(const Number &obj) = default;
    // no const with move assignment operator since we need to alter the obj object.
    Number& operator=(Number &&obj) noexcept = default;
};

Number createNumber(int value){
    Number n{value};
    return n;
}

int main(){
    Number n1{1};
    auto n2{n1};
    n2 = n1;

    auto n3{createNumber(2)};
    n3 = createNumber(3);


    return 0;
}

/*
Resource Management
- Some classes own a Resource
- This resource may be a pointer, file handle, socket, etc.
- Such Resources may be acquired in the constructor
- Subsequently, you have to decide the action in case objects
of such classes are copied, moved, or destroyed.
-e.g. on destruction, the resource must be released to avoid leaks
- Similarly, on copy or move, the resource must be handled accordingly

Solution:
- Use Rule of 5
- Define destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator
- If you define any of the above, you should define all of them


-Rule of 0
- If a class does not own any resource, it does not need to define any of the above
- This is called Rule of 0
- This way the compiler will automatically synthesize the necessary functions
- Providing user-defined implementations of some functions will prevent
the compiler from synthesizing others.

Overall:

Custom Impl         Copy Constructor  Copy Assignment  Move Constructor  Move Assignment      Destructor
Copy Constructor       Custom             =default         =delete           =delete          =default
Copy Assignment        default            custom           =delete           =delete          =default
Move constructor       =delete            =delete          custom            =delete          =delete
Move assignment        =delete            =delete          =delete           custom           =default
Destructor            =default            =default         =delete           =delete          =custom
No Impl               =default            =default         =default          =default         =default  

=default means that the compiler will synthesize the function.
=delete means that the compiler will not synthesize the function.

*/