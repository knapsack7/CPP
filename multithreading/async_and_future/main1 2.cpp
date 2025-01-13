#include<iostream>
#include<future>
#include<chrono>
#include<thread>


bool bufferedFileLoader(){
	size_t bytesLoaded = 0;
	while(bytesLoaded < 20000){
		std::cout<<"thread: loading file..."<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		bytesLoaded += 1000;
	}
	return true;
}

int main(){

	std::future<bool> bgThread = std::async(std::launch::async, bufferedFileLoader);
	
	std::future_status status;

	while(true){
		std::cout<<"Main Thread is running"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		status = bgThread.wait_for(std::chrono::milliseconds(1));
		// If our data is ready, that is, our background thread has completed
		if(status == std::future_status::ready){
			std::cout<<"Our Data is ready..."<<std::endl;
			break;
		}
		
	}
	std::cout<<"Program has completed\n"<<std::endl;
	return 0;
}
