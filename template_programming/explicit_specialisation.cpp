#include <iostream>
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

// Primary template
template<typename T>
T maxx(T a, T b) {
    std::cout << "Type: " << demangle(typeid(T).name()) << std::endl;
    return a > b ? a : b;
}


//Explicit Instantiation
//template char maxx<char>(char, char);


// Explicit Specialization
template<> const char* maxx<const char*>(const char* a, const char* b) {
    std::cout << "const char* specialization" << std::endl;
    return strcmp(a, b) > 0 ? a : b;
}


/*
 * Explicit Specialization
 * Templates specialized for a particular type
 * provides correct semantics for some datatype
 * Or implement an algorithm optimally for a specific type
 * Explicitly specialised functions must be defined in .cpp file
 * Primary template definition should occur before specialization
 */


int main(){
    // Using std::string
    std::string str1{"B"};
    std::string str2{"A"};
    std::cout << "Using std::string: " << maxx(str1, str2) << std::endl;

    // Using const char*
    const char* b{"B"};
    const char* a{"A"};
    std::cout << "Using const char*: " << maxx(b, a) << std::endl;
    
    return 0;   
}