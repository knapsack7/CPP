#include <iostream>
#include <thread>
#include <future>

void downloader(){
    using namespace std::chrono_literals; // c++14 additional literals for std::chrono
    for(int i = 0; i < 10; ++i){
        std::cout<< "."<<std::flush;;
        std::this_thread::sleep_for(300ms); // std::chrono::seconds(1)
    }
}

// task is something which automatically starts a thread and returns a future
// we can use this to start a thread and get the result of the thread
// u need to use async to start a task declared in header future

// async returns a object of type std::future<void>
// we can use this to get the result of the thread

int main(){
    // Case 1: Not storing the future
    //std::async(downloader);  // This will wait for completion before continuing!
    // this will work as synchronously
    //std::cout << "This might not print immediately" << std::endl;

    // Case 2: Storing the future
    std::future<void> result = std::async(downloader);
    std::cout << "This will print immediately" << std::endl;
    
    // We can explicitly wait when we want to
    //result.wait();  // Wait for the task to complete
    result.get(); // this will wait for the task to complete
    std::cout << "\nTask completed" << std::endl;

    return 0;
}

/*
 * Std::async is a wrapper around std::thread
 * It is a template function that takes a callable object and returns a future
 * The callable object can be a function, a lambda expression, or a class that 
 * overloads the function call operator
 * 
 * std::async is a wrapper around std::thread
 * It is a template function that takes a callable object and returns a future
 * The callable object can be a function, a lambda expression, or a class that 
 * overloads the function call operator
 * 
 * Overload:
 * future<return_type> std::async(callable_object, args);
 * future<return_type> async(launch policy, callable_object, args);
 * 
 * std::launch::deferred: The task is executed asynchronously
 * std::launch::async: The task is executed in a new thread
 * 
 * Call to std::async without a launch policy may not always start a new thread
 *      depends on the compiler implementation
 *      to force std::async to execute the task asynchronously, use the async launch
 *      policy explicitly
 * 
 * 
 * If new thread cannot be created with async launch policy, std::system_error exception
 * is thrown
 * 
 * Task Arguments & return Value:
 * Arguments can be specified in std::async for the task
 * By default, the arguments are passed by value
 * to pass by reference, use the reference wrapper, std::ref()
 *       for const reference, use std::cref()
 * To get a value from a task, simply return it from the corresponding function
 * This value is available through the std::future object
 * 
 * std::future
 * 
 * 
 * Used for communication between threads
 * Has a shared state that can be accessed by multiple threads
 * Created through a std::promise object
 *       created by std::async, that directly return a future object
 *       std::promise is an input channel
 *       std::future is an output channel
 * The thread that reads the shared state will wait until the future is ready(with the shared state)
 * Promise/future pair allow safe data sharing between threads
 */

