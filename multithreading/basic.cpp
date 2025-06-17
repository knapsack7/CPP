#include <iostream>
#include <thread>
#include <list>
#include <string>
#include <functional>  // for std::ref

std::list<int> g_Data;

const int SIZE = 5000000;

class String{
public:
    String(){
        std::cout << "String ()" << std::endl;
    }
    String(const String &){
        std::cout << "String (copy)" << std::endl;
    }
    String(String &&) {
        std::cout << "String (move)" << std::endl;
    }
    String & operator=(const String &){
        std::cout << "operator=(const String &)" << std::endl;
        return *this;
    }
    ~String(){
        std::cout << "~String ()" << std::endl;
    }
};

void Download(String &file){
    //std::cout << "[Downloader] Started download of file: " << file << std::endl;
    for(int i = 0; i < SIZE; i++){
        g_Data.push_back(i);
    }
    std::cout << "[Downloader] Download complete" << std::endl;
}


int main(){
    // std::cout << "{main} user started an operation" << std::endl;
    // Download();
    // std::cout << "{main} user operation is completed" << std::endl;

    String file;
    std::cout << "{main} user started an operation" << std::endl;
    //always use std::ref when passing by reference to a thread
    // for constant reference, use std::cref
    std::thread t1(Download, std::ref(file));
    // std::thread t2(Process);

    // t1.detach(); // u cant join a detached thread

    // so need to check if the thread is joinable
    // note once a thread becomes detached, it can never 
    // be joinable again
    // if (t1.joinable()){
    //     t1.join();
    // }
    t1.join();
    std::cout << "{main} user operation is completed" << std::endl;
    return 0;
}