#include <iostream>
#include <thread>
#include <future>

int operation(int count){
    using namespace std::chrono_literals;
    int sum{};
    for(int i = 0; i < 10; ++i){
        sum += i;
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(300ms);
    }
    return sum;
}

int main(){
    using namespace std::chrono_literals;
    /*In defered case task is not executed immediately
     * it is executed when get() or wait() is called on the future
     * 
     * In async case, the task is executed in a new thread
     * and the main thread continues execution
     * 
     */
    std::future<int> result = std::async(std::launch::deferred, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues execution" << std::endl;
    /* Once u call get on a future, the future is no longer valid
     * so u cannot call get again
     * 
     * result.get();
     * result.get(); // this will throw an exception
     */
    if (result.valid()){
        std::cout << "result: " << result.get() << std::endl;
    }
    else{
        std::cout << "result is not valid" << std::endl;
    }

    return 0;
}