#include <iostream>
#include <thread>
#include <future>

void downloader(){
    using namespace std::chrono_literals; // c++14 additional literals for std::chrono
    for(int i = 0; i < 100; ++i){
        std::cout<< "."<<std::flush;;
        std::this_thread::sleep_for(300ms); // std::chrono::seconds(1)
    }
}


int main(){
    downloader();
    std::cout << "main thread continues execution" << std::endl;

    return 0;

}