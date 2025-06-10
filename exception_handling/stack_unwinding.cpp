#include <iostream>
#include <limits>
#include <memory>
using namespace std;

class Test {
public:
    Test(){std::cout<<"Test(): Acquire resources"<<std::endl;}
    ~Test(){std::cout<<"~Test(): Release resources"<<std::endl;}
};


// avoid manual memory management
// Use smart pointers to manage resources
// and containers

int processRecord(size_t count){
    // Test t; // will be destroyed if exception occurs
    // which is something we may not want
    
    //Test *t = new Test(); // t will be destroyed if exception occurs
    // leading to memory leak as Test will be dangling object in the HEAP

    // To avoid these issues, we can use smart pointers
    unique_ptr<Test> t(new Test()); // when t destroys, it will
    // automatically call the destructor of Test
    // and release the resources
    
    if (count < 10)
        throw std::out_of_range("Count is too small");
    
    // Try to allocate a ridiculously large amount of memory
    size_t size = count * sizeof(int);
    cout << "Attempting to allocate " << size << " bytes" << endl;
    
    int *pArray = (int*)malloc(size);
    if(pArray == nullptr){
        cout << "Memory allocation failed, throwing exception" << endl;
        throw std::runtime_error("Memory allocation failed");
        return -1;
    }
    for(int i = 0; i < count; i++){
        pArray[i] = i;
    }
    free(pArray);  
    return 0; 
}


int main(){
    try{
        processRecord(5);
    }catch(const std::runtime_error &e){
        cout << "Caught exception: " << e.what() << endl;
    }catch(const std::out_of_range &e){
        cout << "Caught out of range exception: " << e.what() << endl;
    }catch(const std::bad_alloc &e){
        cout << "Caught bad allocation exception: " << e.what() << endl;
    }catch(const std::exception &e){ // catch all child classes of exception
        cout << "Caught exception: " << e.what() << endl;
    }catch(...){ // catch exceptions even that are not documented, should be last catch block
        cout << "Caught unknown exception" << endl;
    }
    return 0;
}