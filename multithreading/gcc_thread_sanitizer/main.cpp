#include<iostream>
#include<thread>

static int shared_value = 0;
// this has thread error .i.e data race 
// need to use mutex
void shared_value_increment(){
	shared_value = shared_value + 1;
}

int main(){
	std::vector<std::thread> threads;
	for(int i = 0; i < 100; ++i){
		threads.push_back(std::thread(shared_value_increment));
	}

	for(int i = 0; i < 100; ++i){
		threads[i].join();
	}
	std::cout<< " shared value :"<<shared_value<<std::endl;
	return 0;
}
