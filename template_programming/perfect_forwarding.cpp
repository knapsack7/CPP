#include <iostream>
#include "../smart_pointers/integer.h"
#include <string>
#include <cxxabi.h>

// Helper function to demangle type names
std::string demangle(const char* mangled) {
    int status;
    char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
    if (status == 0) {
        std::string result(demangled);
        free(demangled);
        return result;
    }
    return mangled;
}


class Employee{
    std::string m_name;
    Integer m_id;
public:
    template<typename T1, typename T2>
    Employee(T1 &&name, T2 &&id) : m_name{std::forward<T1>(name)},
    m_id{std::forward<T2>(id)}{
        std::cout << "Type of name: " << demangle(typeid(name).name()) << std::endl;
        std::cout << "Type of id: " << demangle(typeid(id).name()) << std::endl;
        std::cout << "Employee(const std::string &&, const Integer &&) called" << std::endl;
    }
    void print() const{
        std::cout << "Name: " << m_name << ", ID: " << m_id.GetValue() << std::endl;
    }
};

template<typename T1, typename T2>
Employee *create(T1 && a, T2 && b){
    return new Employee(std::forward<T1>(a), std::forward<T2>(b));
}


int main(){
    //Integer I(10);
    //Employee emp{std::move("John Doe"), std::move(I)};
    //std::string name{"Manoj Verma"};
    //Employee emp2{name, 123}; // this called Integer Copy Constructor
    // so to cover all the cases, we would have to write 4 constructors
    // . But No worries, we have perfect forwarding to the rescue

    auto emp2 = create("Manoj Verma", Integer{1234});

    return 0;
}