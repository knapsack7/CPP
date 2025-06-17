#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <pthread.h>

void process(){
    // Set thread name
    pthread_setname_np("ProcessThread");
    
    // Get and print thread name
    char threadName[256];
    pthread_getname_np(pthread_self(), threadName, sizeof(threadName));
    std::cout << "Thread name: " << threadName << std::endl;
    std::cout << "process started" << std::endl;

    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < 100; ++i){
        std::cout << i << " "<< std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){
    std::thread t1(process);
    auto it = t1.get_id();
    std::cout << "t1 id: " << it << std::endl;
    t1.native_handle();

    t1.join();
    std::cout << "t1 joined" << std::endl;

    int cores = std::thread::hardware_concurrency();
    std::cout << "cores: " << cores << std::endl;
    
    return 0;
}