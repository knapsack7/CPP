#include <iostream>
#include <chrono>



template<typename T, int size, typename Comparator>
void customSort(T (&arr)[size], Comparator comp) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (comp(arr[j + 1], arr[j])) {
                // Swap elements
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


/*
This is possible because in C++, when you declare an array with an initializer
list like int arr[]{64, 34, 25, 12, 22, 11, 90}, the size is part of the
array's type information. The compiler knows the exact size at compile time.
*/

// Function to print array
template<typename T, int size>
void printArray(T (&arr)[size]) {
    std::cout << "Array: ";
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}


template<typename T, int size, typename callback>
void forEach(T (&arr)[size], callback fn){
    for(int i = 0; i < size; i++){
        fn(arr[i]);
    }
}

class Prodcut{
    std::string name;
    float price;
public:
    Prodcut(std::string name, float price) : name(name), price(price) {}
    void print() const {
        std::cout << "Name: " << name << " Price: " << price << std::endl;
    }
    void assignFinalPrice(float tax){
        float taxes[]{12,3,5};
        float basePrice{price};
        forEach(taxes, [this, basePrice](float tax){
            float taxedPrice = basePrice * tax /100;
            price += taxedPrice;
        });
        print();
    }
    float getPrice() const {
        return price;
    }
};

int main() {
 

    // Prodcut p{"Laptop", 1000};
    // p.assignFinalPrice(10);
    // std::cout << "Final Price: " << p.getPrice() << std::endl;

    // you can have lambda inside lambda

    [](int x)mutable{
        x *=2;
        [](int x) mutable{
            x *= 3;
            std::cout << x << std::endl;    
        }(x);
    }(11111);

    // if capture list is empty,
    // then the lambda will act as a function pointer
    // and u can use it as a callback

    // there is a function atexit() in c
    // which runs just before the program exits
    // u can register a lambda to be called at exit

    atexit([](){
        std::cout << "At exit" << std::endl;
    });
    



    int arr[]{1,2,3,4,5,6,7,8,9,10};
    // Test 1: Direct loop
    auto start1 = std::chrono::high_resolution_clock::now();
    // for(int i = 0; i < 10; i++) {
    //     arr[i] = arr[i] * 2;  // Simple operation
    // }
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);

    // Test 2: Using lambda
    auto start2 = std::chrono::high_resolution_clock::now();
    // forEach(arr, [](auto& x) {
    //     x = x * 2;  // Same operation
    // });
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

    std::cout << "Direct loop time: " << duration1.count() << " microseconds\n";
    std::cout << "Lambda time: " << duration2.count() << " microseconds\n";


    // offset inside lambda is captured by value
    // so it is different form outside offset
    // remember lambda offset variable will give
    // u compilation error if u try to modify it
    int offset = 5;
    // forEach(arr, [offset](auto& x){
    //     x = x + offset;
    //     // ++offset; this will give u compilation error
    // });


    // mutable will remove the constness of offset
    // so u can modify it inside lambda

    //The mutable keyword not only allows modification of the
    // captured value but also makes that modified value persist 
    // between lambda invocations.
    // bz internally lambdas are represented as a class and
    // captured parameter are stored as member variables of that class
    // so when u use mutable keyword, u are actually modifying the member variable
    // and not the original variable and for the subsequent lambda invocations
    // the modified value will be used
    // forEach(arr, [offset](auto& x) mutable {
    //     //std::cout << "Current offset: " << offset << std::endl;
    //     x = x + offset;
    //     ++offset;
    // });

    //printArray(arr);

    //int sum{};

    // [&sum] will capture sum by reference
    // so any modification to sum will be reflected in the outer scope
    // and for the subsequent lambda invocations
    // the modified value will be used from its member variable
    // of anonymous class
 

    // if u need to capture all variables by reference
    // u can just use & and it will capture all the variables by 
    // reference
    // forEach(arr, [&sum, &offset](auto& x){
    //     sum += x;
    // });

    // if u need to capture all variables by value
    // u can just use = and it will capture all the variables by 
    // value

    // forEach(arr, [=](auto& x){
    //     sum += x; // compilation error as its not captured by reference
    //     // and they are const
    // });

    // std::cout << "Sum: " << sum << std::endl;

    // global and static variables are automatically captured by value
    // so u don't need to capture them
    


    return 0;
}

/*
 *      Capture mode                explanation
 *      [var]                       capture var by value
 *      [&var]                      capture var by reference
 *      [=]                         capture by value
 *      [this]                      capture this (captures all member variables)
 *      [&]                         capture all variables by reference
 *      [=]                         capture all variables by value
 *      [&, var]                    capture all variables by value except var by reference
 *      [=, &var]                   capture all variables by reference except var by value
 *      [this, &var]                capture this pointer by reference and var by value
 *      [this, var]                 capture this pointer by value and var by value
 */