#include <iostream>
#include <string_view>

#pragma region ex1
// we used string_view bz msg is not getting change and we want to avoid copying the string
void prettyPrint(std::string_view msg, char c){
    for(size_t i = 0; i < msg.length(); ++i){
        std::cout << c;
    }
    std::cout << std::endl;
    std::cout << msg << std::endl;
}

#pragma endregion

#pragma region ex2

enum class Title{MR, MRS, MS};

// we replace const std::string &last with std::string_view last because we don't want to copy the string
// we want to avoid copying the string and we saved the cost of one std::string object
std::string & combineName(std::string &name, std::string_view last, Title s){
    switch(s){
        case Title::MR:
            name.insert(0, "Mr. ");
            break;
        case Title::MRS:
            name.insert(0, "Mrs. ");
            break;
        case Title::MS:
            name.insert(0, "Ms. ");
    }
    return name += last;
}

#pragma endregion

#pragma region ex3

class Person{
    std::string m_Name;
public:
    Person(std::string name): m_Name(std::move(name)){}
    void print() const{
        std::cout << m_Name << std::endl;
    }
};

Person createPerson(std::string_view name){
    std::string n{name};
    Person p{n};
    return p;
}

void withClass(){
    using namespace std::string_literals;
    std::string n{};
    Person p{createPerson("Bruce Wayne")};

    p.print();
}


#pragma endregion



int main(){
    //prettyPrint("Hello World", '#');
    // std::string name = "John";
    // std::string last = " Doe";
    // std::cout << combineName(name, last, Title::MR) << std::endl;
    withClass();
    return 0;
}

/*
 *  WHEN TO USE STRING_VIEW:
 * Dont pass in functions that accept a C-style string bz it might not have a null terminator
 * Do not return string_view to string from a function
 * Do not assign temporary strings to string views
 * Avoid as class members
 */