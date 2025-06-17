#include <iostream>
#include <thread>
#include <future>

int operation(int count){
    using namespace std::chrono_literals;
    int sum{};
    for(int i = 0; i < 10; ++i){
        sum += i;
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(30ms);
    }
    return sum;
}

int main(){
    using namespace std::chrono_literals;
   
    std::future<int> result = std::async(std::launch::async, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues execution" << std::endl;
    
    if (result.valid()){
        // First check with wait_for
        // auto status = result.wait_for(4s); // it waits until the shared state is ready
        // switch(status){
        //     // Case 1: Task has completed successfully and result is available
        //     // This is the ideal case where the async operation finished within the timeout period
        //     case std::future_status::ready:
        //         std::cout << "result is ready" << std::endl;
        //         break;
            
        //     // Case 2: Task is still running and didn't complete within the specified timeout
        //     // This indicates the operation is taking longer than expected
        //     case std::future_status::timeout:
        //         std::cout << "result is not ready still running" << std::endl;
        //         break;
            
        //     // Case 3: Task hasn't started yet because it was created with deferred policy
        //     // The task will only start when get() or wait() is called
        //     case std::future_status::deferred:
        //         std::cout << "result is deferred. It is synchronous" << std::endl;
        //         break;
        // }

        // Then check with wait_until
        /* wait_until vs wait_for:
         * - wait_until: Waits until a specific point in time (absolute time)
         * - wait_for: Waits for a specific duration (relative time)
         * 
         * wait_until is useful when:
         * 1. You need to wait until a specific calendar time
         * 2. You want to implement timeouts that align with system clock
         * 3. You need to coordinate multiple operations to complete by a specific time
         * 
         * In this example, we're waiting until 4 seconds from now
         */
        auto timepoint = std::chrono::system_clock::now();
        timepoint += 4s;
        auto status2 = result.wait_until(timepoint);
        switch(status2){
            case std::future_status::ready:
                std::cout << "result is ready (wait_until)" << std::endl;
                break;
            case std::future_status::timeout:
                std::cout << "result is not ready (wait_until)" << std::endl;
                break;
            case std::future_status::deferred:
                std::cout << "result is deferred (wait_until)" << std::endl;
                break;
        }

        result.wait(); // it waits until the shared state is ready
        // it doesnt return the state as .get() does
        std::cout << "result: " << result.get() << std::endl;
    }
    else{
        std::cout << "result is not valid" << std::endl;
    }

    return 0;
}