#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

static int shared_value = 0;
std::mutex mtx;

void shared_value_increment(){
	std::lock_guard<std::mutex> lock(mtx);
	shared_value = shared_value + 1;
}



int main(){

	std::vector<std::thread> threads;
	for(int i = 0; i  < 10; ++i){
		threads.push_back(std::thread(shared_value_increment));
	}

	for(int i = 0; i < 10; ++i){
		threads[i].join();
	}
	
	std::cout<<"shared value :"<<shared_value<<std::endl;
	return 0;
}
