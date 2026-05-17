#include <iostream>
#include <thread>

int task1(){
    std::cout << "Task1 started" << std::endl;
    return 0;
}

int task(){
    std::cout << "Task started" << std::endl;
    std::thread t1(task1);
    try{
        throw std::runtime_error("Exception in task");
        if (t1.joinable()) t1.join();
    }catch(const std::exception& e){
        std::cout << "Exception caught: " << e.what() << std::endl;
        if (t1.joinable()) t1.join();
    }
    return 0;
}

int main(){
    std::thread t(task);
    try{
        throw std::runtime_error("Exception in main");
        if (t.joinable()) t.join();
    }catch(const std::exception& e){
        std::cout << "Exception caught: " << e.what() << std::endl;
        if (t.joinable()) t.join();
    }
    return 0;
}