/* Promise
 * Provides a way to store a value or an exception
 * This is called the shared state
 * This state can be accessed later from another thread through a
 * future object
 * Promise/Future are two endpoints of a communication channel
 * One operation stores a value in a promise and the other operation will retrieve
 * it through a future asynchronously
 * These operations are synchronized, therefore, thread-safe
 * Promise object can be used only once. this means you can set a value or an exception in it only once.
 */

#include <iostream>
#include <thread>
#include <future>

// Example 1: Main thread throwing exception to task
int operation(std::promise<int>& data){
    using namespace std::chrono_literals;
    auto f = data.get_future();
    try {
        std::cout << "[thread] waiting for count" << std::endl;
        auto count = f.get(); // will block until the promise is set
        // or data is provided by main thread
        // In a way main thread is notifying the task
        std::cout << "[thread] count received" << std::endl;
        int sum{};
        for(int i = 0; i < 10; ++i){
            sum += i;
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(300ms);
        }
        return sum;
    } catch (const std::exception& e) {
        std::cout << "[thread] exception: " << e.what() << std::endl;
        // In task: We use current_exception() because we're in the catch block
        // where the exception is currently being handled
        data.set_exception(std::current_exception());
    }
    return 0;
}

// Example 2: Task throwing exception to main thread
int operation2(std::promise<int>& data) {
    using namespace std::chrono_literals;
    try {
        // Simulate some work
        std::this_thread::sleep_for(1s);
        // Task throws an exception
        throw std::runtime_error("Task failed to complete");
        
        // This code won't execute due to exception
        data.set_value(42);
        return 42;
    } catch (...) {
        // In task: We use current_exception() because we're in the catch block
        // where the exception is currently being handled
        data.set_exception(std::current_exception());
        throw; // Re-throw to ensure the task fails
    }
}

int main(){
    using namespace std::chrono_literals;
    
    // Example 1: Main thread throwing exception to task
    std::cout << "\nExample 1: Main thread throwing exception to task\n";
    std::promise<int> data;
    std::future<int> result = std::async(std::launch::async, operation, std::ref(data));
    std::this_thread::sleep_for(2s);
    try {
        throw std::runtime_error{"data not available"};
        data.set_value(10);
        if (result.valid()){    
            std::cout << "main() thread continues execution" << std::endl;
            std::cout << "result: " << result.get() << std::endl;
        }
    }catch (const std::exception& e){
        std::cout << "main() thread caught exception: " << e.what() << std::endl;
        // In main: We use make_exception_ptr because we're creating a new
        // exception pointer from an existing exception object
        data.set_exception(std::make_exception_ptr(e));
    }

    // Example 2: Task throwing exception to main thread
    std::cout << "\nExample 2: Task throwing exception to main thread\n";
    std::promise<int> data2;
    std::future<int> result2 = std::async(std::launch::async, operation2, std::ref(data2));
    
    try {
        // Wait for the result, this will throw if the task threw an exception
        int value = result2.get();
        std::cout << "Task completed successfully with value: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Main thread caught exception from task: " << e.what() << std::endl;
    }

    return 0;
}