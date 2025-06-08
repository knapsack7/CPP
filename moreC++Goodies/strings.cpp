#include <iostream>
#include <string>
#include <cstring>

// const char* combine(const char* str1, const char* str2){
//     // 1 extra byte for null terminator
//     char* result = new char[strlen(str1) + strlen(str2) + 1];
//     strcpy(result, str1);
//     strcat(result, str2);
//     return result;
// }

std::string combine(const std::string& str1, const std::string& str2){
    return str1 + str2;
}

int main(){
    // char first[10];
    // char last[10];
    // std::cin.getline(first, 10);
    // std::cin.getline(last, 10);

    // const char* full = combine(first, last);
    // std::cout << full << std::endl;
    // delete[] full;

    // intialize and assign
    std::string str1 = "Hello";
    std::string str2 = "";
    str2 = "World";
    std::string str3 = str1 + str2;
    std::cout << str3 << std::endl;

    // access
    std::cout << str1[0] << std::endl;
    std::cout << str1.at(0) << std::endl;

    std::getline(std::cin, str1);
    std::cout << str1 << std::endl;

    // size
    std::cout << str1.size() << std::endl;
    std::cout << str1.length() << std::endl;

    // empty


    // Insert and concatenate
    std::string s1{"Hello"}, s2{"World"};
    std::string s = s1 + s2;

    s += s1;

    s.insert(6, "Happy");
    // comparison

    if (str1 == str2){
        std::cout << "Equal" << std::endl;
    }
    else{
        std::cout << "Not Equal" << std::endl;
    } 

    // Removal
    s.erase();
    s.erase(0, 5);
    // Search
    auto pos = s.find("World", 0); // time complexity is O(n*m) Uses Naive Algorithm
    if (pos != std::string::npos){
        std::cout << "Found at " << pos << std::endl;
    }
    else{
        std::cout << "Not Found" << std::endl;
    }

    // replace
    s.replace(0, 5, "Happy");
    // substr
    std::string sub = s.substr(0, 5);
    std::cout << sub << std::endl;
    // find_first_of
    auto pos2 = s.find_first_of("World", 0);
    std::cout << "Found at " << pos2 << std::endl;


    std::string first;
    std::string last;

    std::getline(std::cin, first);
    std::getline(std::cin, last);

    std::string full = combine(first, last);
    std::cout << full << std::endl;


    std::string name{"Manoj Verma"};
    unsigned int value = 100u;

    using namespace std::literals;
    auto n2 = "Manoj Verma"s;

    return 0;
}