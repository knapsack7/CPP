#include <iostream>
using namespace std;
#include <optional>

/*
 * Std::Optional
 * A new library type that can be used a function may or may not
 * return a value
 * If it does not return a value, a common way is to compare with a 
 * predefined value such as 0, nullptr, true/false etc.
 * This leads to different kinds of checks for different types
 * Std::optional<T> can represent a type that may or may not contain a value
 *     often called a nullable type
 * Properties:
 * No value is represented by std::nullopt
 * std::optional is a value type - so, it can be copied through
 * deep copy 
 * Does not need to allocate any memory on heap
 * You can not store references inside std::optional
 * Provides several overloaded operators and functions to access the value inside safely
 * May throw std::bad_optional_access if the value is not present
 */

const char * getErrorString(int errorNo){
    switch(errorNo){
        case 0:
            return "Invalid Input";
        case 1:
            return "Connection not established yet";
        default:    
            return "";
    }
}

std::optional<const char *> getErrorStringOptional(int errorNo){
    switch(errorNo){
        case 0:
            return "Invalid Input";
        case 1:
            return "Connection not established yet";
        default:    
            return std::nullopt; // this means no value is present
    }
}

class ContactName{
    std::string firstName;
    std::optional<std::string> middleName;
    std::string lastName;
public:
    ContactName(const std::string &firstName, const std::optional<std::string> &middleName, const std::string &lastName):
    firstName(firstName), middleName(middleName), lastName(lastName){}
    
    void print(){
        cout << firstName << " ";
        cout << middleName.value_or("") << " ";
        cout << lastName << endl;
    }
};


int main(){
    

    ContactName n1{"Manoj", "Kumar", "Verma"};
    ContactName n2{"Swapnil", std::nullopt, "Verma"};

    n1.print();
    n2.print();

    // std::optional<int> value{0};

    // //safer
    // if(value.has_value()){
    //     cout << value.value() << endl;
    // }
    // // risky
    // if (value){
    //     cout << *value << endl;
    // }
    
    
    // auto message = getErrorString(1);


    // if (strlen(message) > 0){
    //     cout << "Error: " << message << endl;
    // }
    // else{
    //     cout << "Unknown error number" << endl;
    // }

    // auto message = getErrorStringOptional(4);
    // if (message.has_value()){
    //     cout << "Error: " << message.value() << endl;
    // }
    // else{
    //     cout << "Unknown error number" << endl;
    // }

    // auto message = getErrorStringOptional(4);

    // // returns the value if present, otherwise returns the default value
    // std::cout << message.value_or("Default message") << endl;

    // if (message.has_value()){
    //     // throws an exception std::bad_optional_access if the value is not present
    //     cout << "Error: " << message.value() << endl;
    // }
    // else{
    //     cout << "Unknown error number. optional returns std::nullopt" << endl;
    // }

    return 0;
}