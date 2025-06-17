#include <iostream>
#include <thread>
#include <list>
#include <string>
#include <functional>  // for std::ref
#include <future>     // for std::packaged_task


int add(int a, int b){
    return a + b;
}

int square(int x){
    return x * x;
}

int compute(const std::vector<int> &data){
    using namespace std;
    int sum{};
    for (auto e : data){
        sum += e;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<< "."<<std::flush;
    }
    return sum;
}
// future is a class template that represents a value that is not yet available
// it is used to get the result of a thread

int main(){
    std::packaged_task<int(int, int)> task(add);
    // std::future<int> ft = task.get_future();
    // task(3, 5);
    // std::cout << "Result: " << ft.get() << std::endl;

    std::packaged_task<int(const std::vector<int> &)> task2(compute);
    std::future<int> ft2 = task2.get_future();
    std::vector<int> data{1, 2, 3, 4, 5, 6};
    //task2(data);
    std::thread threadCompute(std::move(task2), data);
    std::cout << "threadCompute started" << std::endl;
    threadCompute.join();
    std::cout << "\nResult: " << ft2.get() << std::endl; // main will block here

    std::cout << "main thread ended" << std::endl;
    return 0;
}