#include <string_view>
#include <iostream>

/*
 * STD::STRING_VIEW
 * allows us to deal with character sequences without 
 * allocating memory
 * Can be considered as a kind of reference to a character sequence
 * Can be used wherever a non-modifiable string in required
 * It simply stores a pointer to the character array along with its
 * length
 * It is fast and cheap to copy
 * However, it should be used carefully as it can lead to bugs
 * 
 * Properties:
 * Underlying sequence is read-only
 * It can be accessed through data() method
 *      may return a nullptr
 *      a character sequence without null terminator
 * You can only assign a new value, swap values, and shrink
 * it to a subset
 * Character sequence is not guaranteed to be null-termninated
 *      consequently, may not work with c String functions
 * NO ALLOCATOR SUPPORT
 */

int main(){
    using namespace std::literals;

    std::string_view sv1 = "Hello world";

    std::string str1{"Hello"};
    std::string_view sv2 = str1;

    auto sv3 = "Using\0literals"sv;

    std::cout << "Size:" << sv3.length() << std::endl;
    std::cout << sv3 << std::endl;

    std::cout << "data()" << sv3.data() << std::endl;

    std::cout << "character default" << sv3[0] << std::endl;

    std::cout << "character default" << sv3.at(0) << std::endl;

    auto f = sv3.find("literals");
    if (f != std::string::npos){
        std::cout << "Found at position" << f << std::endl;
    }

    sv3.remove_prefix(3);
    std::cout << sv3 << std::endl;

    sv3.remove_suffix(3);
    std::cout << sv3 << std::endl;

    sv3.remove_suffix(3);
    std::cout << sv3 << std::endl;

    auto sv4 = sv3.substr(0, 3);
    std::cout << sv4 << std::endl;
    
    return 0;

}