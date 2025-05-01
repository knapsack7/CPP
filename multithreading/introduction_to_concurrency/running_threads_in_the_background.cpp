#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>

void Daemon(){
	while(1){
		std::cout << "I am Daemon thread, No one can kill me except process is terminated" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

int main(){
	std::thread t1(Daemon);
	//running in the background
	t1.detach();
	// main thread will sleep for 5 secs
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	return 0;
}
