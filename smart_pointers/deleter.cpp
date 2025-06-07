#include <iostream>
#include <memory>
#include <cstdlib>

struct Free {
    void operator()(int *p){
        std::cout<<"Freeing memory"<< std::endl;
        free(p);
    }
};

void malloc_free(int *p){
    std::cout<<"Freeing memory"<< std::endl;
    free(p);
}

void unique_ptr_deleters(int *raw_ptr){
    // by default, shared_ptr and unique_ptr uses delete to free the memory
    // but we can use custom deleter to free the memory
    //std::unique_ptr<int, Free> p{(int*)malloc(sizeof(int)), Free{}};
    std::unique_ptr<int, void (*)(int*)> smart_ptr{(int*)malloc(sizeof(int)), malloc_free};
}

void shared_ptr_deleters(int *raw_ptr){
    // by default, shared_ptr and unique_ptr uses delete to free the memory
    // but we can use custom deleter to free the memory
    //std::shared_ptr<int> p{(int*)malloc(sizeof(int)), Free{}};
    std::shared_ptr<int> smart_ptr{(int*)malloc(sizeof(int)), malloc_free};
}

int main(){
    int *p = (int*)malloc(sizeof(int));
    //unique_ptr_deleters(p);
    
    // for shared_ptr, deleters are defined in a slightly different way
    shared_ptr_deleters(p);
    *p = 100;
    std::cout<<"Value is : " << *p << std::endl;
    return 0;
}