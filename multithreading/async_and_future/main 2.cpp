#include<iostream>
#include<future>
#include<thread>



int computeSum(int a, int b){
	return a+b;
}

int main(){
	std::cout<< "Starting async Operation..\n";
	//Launch Async task
	std::future<int> result = std::async(std::launch::async, &computeSum, 8, 9);
	//Do other work while the async task is running
	std::cout<<"Doing other work in the main thread\n";
	//wait for the result ans retrive it
	int sum = result.get(); // Blocks until the result is ready Not No need to write join
	std::cout<<"The Sum is : "<<sum<<std::endl;
	return 0;	
	
}
