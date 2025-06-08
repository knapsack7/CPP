#include <iostream>
#include <sstream>
#include <string>

int main(){
    int a{5}, b{6};

    int sum = a + b;
    
    // error: not allowed to concatenate string and int
    // std::string output = "sum of" + a + " & " + b + " is " + num;
    std::stringstream ss; // read and write
    std::stringstream is; // read
    std::stringstream os; // write

    ss << "sum of " << a << " & " << b << " is " << sum;
    std::string s = ss.str();
    std::cout << s << std::endl;
    ss.str("");
    ss << sum;
    auto ssum = ss.str();
    std::cout << ssum << std::endl;

    ssum = std::to_string(sum);
    std::cout << ssum << std::endl;

    std::string data = "12 89 21";
    int d;

    ss.str(data);;
    while(ss >> d){
        ss >> d;
        std::cout << d << std::endl;
    }

    int x = std::stoi("54");


    return 0; 
}