#include <iostream>
#include <thread>

void printMessage(){
	std::cout << "Hello from thread!"<<std::endl;
}

int main(){
	std::thread t(printMessage); // create a thread and runs printMessage
	 // join() waits for the thread to complete
    // If you don't join, program might terminate before thread completes

	if(t.joinable())
		t.join();
	
	std::thread t2([](){
		std::cout<<"Thread2 Running\n"<<std::endl;
	});

	if (t2.joinable()){
		t2.join();
	}

	return 0;
}
