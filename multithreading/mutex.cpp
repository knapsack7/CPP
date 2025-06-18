#include <iostream>
#include <thread>
#include <list>
#include <string>
#include <mutex>
#include <functional>  // for std::ref

std::list<int> g_Data;

constexpr int SIZE = 10000;

std::mutex g_Mutex;
// always ensure that the mutex is unlocked b4 returning of the thread
// to deal with this we would use RAII (Resource Acquisition Is Initialization)
// which is a pattern that ensures that the mutex is unlocked when the thread returns
// C++ provides a class called std::lock_guard that implements RAII for mutexes
// it is a wrapper class that locks the mutex on construction and unlocks it on destruction
// so we can use it to lock the mutex and ensure that it is unlocked when the thread returns

void Download(){
    //std::cout << "[Downloader] Started download of file: " << file << std::endl;
    for(int i = 0; i < SIZE; i++){
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (i == 6000){
            std::cout << "[Downloader] Download interrupted" << std::endl;
            return;
        }
        g_Data.push_back(i);
    }
    std::cout << "[Downloader] Download complete" << std::endl;
}

void Download2(){
    //std::cout << "[Downloader] Started download of file: " << file << std::endl;
    for(int i = 0; i < SIZE; i++){
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_Data.push_back(i);
    }
    std::cout << "[Downloader] Download complete" << std::endl;
}


int main(){
    
    std::thread thDownloader1(Download);
    std::thread thDownloader2(Download2);

    thDownloader1.join();
    thDownloader2.join();

    std::cout << "g_Data.size(): " << g_Data.size() << std::endl;

    return 0;
}

/*
 * Problem with the Above implementation:
 * 1. The other thread will wait for the mutex to be unlocked if one is occupied with Critical Section
 *    the other thread will go in sleep state and wait for the mutex to be unlocked so if the the CPU is
 *    idle at that moment, the other thread thread will still not able to run so bad utilization of the CPU
 *    .Therefore in general, locks should be avoided if possible.
 * 
 * The other thing we could have done  is that every thread has its own list and we can push all the data to a single
 * list after the thread is done.
 * The performance of the program will be much better than the locking.
 */