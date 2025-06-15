#include <functional>

/*
 * Std::function
 * A general-purpose function wrapper
 * Can store, and invoke and target that can ve invoked with
 * operator() syntax e.g., function pointers & function objects
 * Stored object is called the target
 * This target can be invoked with the same syntax through
 * std::function object
 * Invocation without a target throws std::bad_function_call
 * exception
 * It is a class template
 * 
 * Syantx;
 * 
 * std::function<function signature> object = {callable};
 * 
 * int square(int);
 * int *alloc(size_t bytes);
 * 
 * std::function<int(int)> f1 = square;        //f1(3);
 * std::function<int*(size_t)> f2 = Alloc;     //f2(1024);
 * std::function<bool(int)> f3 = [](int x){return x % 2 == 0;};
 */

#include <iostream>

int square(int x){
    return x * x;
}

int add(int x, int y){
    return x + y;
}

int sub(int x, int y){
    return x - y;
}

struct Max{
    int operator()(int x, int y){
        return x > y ? x : y;
    }
};


int operation(int x, int y, std::function<int(int, int)> callback){
    return callback(x, y);
}



int main(){
    try{
        /*std::function<int(int)> f1 = square;
        std::function<int(int, int)> f2 = add;
        std::function<int(int, int)> f3 = Max();

        std::cout << "f1(3) = " << f1(3) << "\n";
        std::cout << "f2(3, 4) = " << f2(3, 4) << "\n";
        std::cout << "f3(3, 4) = " << f3(3, 4) << "\n";

        std::function<bool(int)> f4 = [](int x){return x % 2 == 0;};
        std::cout << "IsEven ? " << f4(3) << "\n";
        */
       std::function<int(int, int)> f1 = add;
       std::cout << operation(3, 4, f1) << "\n";
       f1 = sub;
       std::cout << operation(3, 4, f1) << "\n";
       f1 = Max();
       std::cout << operation(3, 4, f1) << "\n";
       std::cout << operation(3, 4, [](int x, int y){return x * y;}) << "\n";
    } catch(const std::exception& ex){
        std::cout << "Exception - > " << ex.what() <<"\n";
    }
    return 0;
}



