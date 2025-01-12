#include <iostream>
#include <thread>

void printMessage(){
	std::cout << "Hello from thread!"<<std::endl;
}

int main(){
	std::thread t(printMessage); // create a thread and runs printMessage
	if(t.joinable())
		t.join();
	return 0;
}
