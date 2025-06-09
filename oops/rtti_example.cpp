#include <iostream>
#include <typeinfo>
#include <cxxabi.h>  // For demangling

/*
 * typeid behavior:
 * 1. Compile-time evaluation:
 *    - When used with non-polymorphic types
 *    - When used with type names directly (not objects)
 *    - When used with built-in types
 *    Example: typeid(int), typeid(std::string)
 * 
 * 2. Runtime evaluation:
 *    - When used with polymorphic types (classes with virtual functions)
 *    - When used with objects of derived classes through base pointers
 *    - When used with dynamic_cast
 *    Example: typeid(*ptr) where ptr is a base class pointer
 */

// Function to demangle type names
std::string demangle(const char* mangled_name) {
    int status;
    char* demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    if (status == 0) {
        std::string result(demangled);
        free(demangled);
        return result;
    }
    return mangled_name;
}

// User defined types
class Base {
public:
    virtual ~Base() {} // Virtual destructor needed for RTTI
};

class Derived1 : public Base {};
class Derived2 : public Base {};

// Template class
template<typename T>
class MyContainer {
    T data;
public:
    MyContainer(T val) : data(val) {}
};

// Custom class with inheritance
class Animal {
public:
    virtual ~Animal() {}
};

class Dog : public Animal {};
class Cat : public Animal {};

int main() {
    // 1. Compile-time typeid (non-polymorphic)
    int x = 42;
    std::cout << "Compile-time typeid: " << demangle(typeid(x).name()) << std::endl;
    std::cout << "Compile-time typeid: " << demangle(typeid(int).name()) << std::endl;
    
    // 2. Runtime typeid (polymorphic)
    Base* ptr = new Derived1();
    std::cout << "Runtime typeid: " << demangle(typeid(*ptr).name()) << std::endl;
    
    // 3. Template class (compile-time)
    MyContainer<int> intContainer(42);
    std::cout << "Compile-time typeid: " << demangle(typeid(intContainer).name()) << std::endl;
    
    // 4. Runtime typeid with inheritance
    Animal* animal = new Dog();
    std::cout << "Runtime typeid: " << demangle(typeid(*animal).name()) << std::endl;
    
    // 5. Dynamic cast (runtime)
    Dog* dog = dynamic_cast<Dog*>(animal);
    if (dog) {
        std::cout << "Successfully cast to Dog" << std::endl;
    }
    
    // 6. Type comparison
    if (typeid(*animal) == typeid(Dog)) {  // Runtime comparison
        std::cout << "animal is a Dog" << std::endl;
    }
    
    delete ptr;
    delete animal;
    return 0;
} 