#include <iostream>
#include <thread>

void printMessage(){
	std::cout << "Hello from thread!"<<std::endl;
}

class MyClass{
    int data;
public:
    MyClass(int d): data(d){}
    void printData(){
        std::cout<<"Class Member Data is : "<<data<<std::endl;
    }
};

int main(){
    // 1. Using Function Pointer
	std::thread t(printMessage); // create a thread and runs printMessage
	 // join() waits for the thread to complete
    // If you don't join, program might terminate before thread completes


    /*
    Thread states:
        joinable(): Thread is running or completed but not joined
        join(): Wait for thread to complete
        detach(): Let thread run independently
        get_id(): Get unique thread identifier

    */

	if(t.joinable())
		t.join();
	
    // 2. Using Lambda Function
	std::thread t2([](){
		std::cout<<"Thread2 Running\n"<<std::endl;
	});

	if (t2.joinable()){
		t2.join();
	}

    // 3. Using Class Member Function
    std::unique_ptr<MyClass> myClass = std::make_unique<MyClass>(10);
    // myClass.get() is used to get the raw pointer to the MyClass object
    // .get() is method of unique_ptr to get the raw pointer to the MyClass object
    std::thread t3(&MyClass::printData, myClass.get());
    if (t3.joinable()){
        t3.join();
    }

    // 4. Using Lambda Function with Capture List   
    std::thread t4([&myClass](){
        myClass->printData();
    });
    if (t4.joinable()){
        t4.join();
    }

	return 0;
}
