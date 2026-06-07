#include <iostream>
#include <thread>
#include <mutex>

static int global_counter = 0;

std::mutex mtx;
void func(){
    for(int i = 0; i < 100000; i++){
        //std::lock_guard<std::mutex> lock(mtx);
        global_counter++;
    }
}

int main(){
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    std::cout << "global_counter: " << global_counter << std::endl;
    return 0;
}