#include <iostream>
#include <thread>
#include <list>
#include <string>
#include <mutex>
#include <functional>  // for std::ref

std::list<int> g_Data;

constexpr int SIZE = 10000;

std::mutex g_Mutex;

void Download(){
    //std::cout << "[Downloader] Started download of file: " << file << std::endl;
    for(int i = 0; i < SIZE; i++){
        g_Mutex.lock();
        //if(i == 6000)return; // this will cause a deadlock
        // always ensure that the mutex is unlocked b4 returning of the thread
        g_Data.push_back(i);
        g_Mutex.unlock();
    }
    std::cout << "[Downloader] Download complete" << std::endl;
}

void Download2(){
    //std::cout << "[Downloader] Started download of file: " << file << std::endl;
    for(int i = 0; i < SIZE; i++){
        g_Mutex.lock();
        g_Data.push_back(i);
        g_Mutex.unlock();
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