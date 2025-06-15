#include <iostream>

/*
 * std::bind
 * Wrapper That can bind some arguments to a function
 * The arguments to the target function are represented
 * using placeholders or directly bound to specific values
 * Placeholders are represented using constant objects of unspecified
 * type in std::placeholders namespace named _1, _2, _3, etc.
 * Can be used to invoke a function that accepts n arguments as
 * a function with n-m arguments
 * Returns a function object through which the target in invoked
 * 
 * Example:
 *      std::bind(callable, arg1, arg2,.....argN);
 * int square(int);
 * void print(const char*);
 * 
 * auto f1 = std::bind(square, 3);   // f1();
 * auto f2 = std::bind(print, _1);  // f2("Hello");
 * 
 */

#include <functional>

int sub(int x, int y){
    return x - y;
}

int add(int x, int y){
    return x + y;
}

void print(const char* str){
    std::cout << str << "\n";
}

struct greaterThan{
    bool operator()(int x, int y) const{
        return x > y;
    }
};

int operation(int x, int y, std::function<int(int, int)> callback){
    return callback(x, y);
}

int accumulate(int x, int y, int z){
    return x + y + z;
}

int main(){

    using namespace std::placeholders;
    // std::function<int(int, int)> f1 = std::bind(sub, std::placeholders::_1, std::placeholders::_2);
    // std::cout << f1(3, 4) << "\n";

    std::function<int(int, int)> f1 = std::bind(sub, _1, _2);
    std::cout << f1(3, 4) << "\n";

    // auto f2 = std::bind(sub, _2, _1);
    // std::cout << f2(3, 4) << "\n";

    // auto f3 = std::bind(add, 10, 5);
    // std::cout << f3() << "\n";

    // auto f4 = std::bind(add, 3, _1);
    // std::cout << f4(4) << "\n";

    // auto gt = std::bind(greaterThan{}, _2, _1);
    // std::cout << gt(3, 4) << "\n"; // operator()(4,3)

    // auto gt = [](int x, int y){
    //     return greaterThan{}(y ,x);
    // };
    // std::cout << gt(6, 2) << "\n";

    // auto acc = std::bind(accumulate, 1, 2, 3);
    // std::cout << acc() << "\n";

    // auto acc2 = std::bind(accumulate, 1, _1, 3);

    // auto acc3 = std::bind(accumulate, _1, _2, 0);
    // std::cout << operation(8, 5, acc3) << "\n";

    auto acc = [](int x, int y){
        return accumulate(x, y, 0);
    };

    std::cout << operation(8, 5, acc) << "\n";

    // value type and constness are preserved here
    // always remember to correctly forward the arguments
    // to calling function. Other code may not work as expected
    auto f = [](auto && x){
        return sub(std::forward<decltype(x)>(x), 5);
    };

    // c++ 20 feature
    auto gt = []<typename T>(T&& x, T&& y){
        return greaterThan{}(std::forward<T>(x), std::forward<T>(y));
    };

    std::cout << gt(6, 2) << "\n";

    std::cout << f(10) << "\n";
    return 0;
}

