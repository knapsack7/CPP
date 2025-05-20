#include<iostream>
#include<thread>
#include "../include/board.h"

int main(){

    for(int i=0; i<10; i++){
        std::thread t1([](){
            try {
                auto& board1 = Board::getInstance();
            } catch(const std::exception& e) {
                std::cout << "Exception: " << e.what() << std::endl;
                std::cout << "Only one instance of Board is allowed" << std::endl;
            }
        });
        t1.join();
    }

    return 0;
}