#include <iostream>
#include <fstream>
#include <string>


void write(){
    std::ofstream out("test.txt");
    if (!out){
        std::cout<<"Could not open file for writing"<<std::endl;
        return;
    }
    std::string msg{"C++ was designed by Bjarne Stroustrup"};
    
    for(char c: msg){
        out.put(c);
    }
    out.seekp(5);
    out.put('#');
    out.close();
}

void read(){
    std::ifstream in("test.txt");
    if (!in){
        std::cout<<"Error opening file"<<std::endl;
        return;
    }
    //in.seekg(-5, std::ios::end);
    std::cout<< "Current position: "<<in.tellg()<<std::endl;
    char ch{};
    while (in.get(ch)){
        std::cout<<ch;
    }
    in.close();
}

void usingFstream(){
    std::fstream stream{"file.txt"};
    if (!stream){
        std::cout<<"Error opening file.. Lets create it"<<std::endl;
        std::ofstream out{"file.txt"};
        out.close();
        stream.open("file.txt");
    }
    stream<<"Hello World"<<std::endl;

    stream.seekg(0);

    std::string line;
    std::getline(stream, line);
    std::cout<<line<<std::endl;
    stream.close();
}

int main(){
    //write();
    //read();
    usingFstream();
    return 0;
}