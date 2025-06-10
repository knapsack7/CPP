#include <iostream>

class A{
public:
    A(){
        std::cout<<"A()"<<std::endl;
    }
    ~A(){
        std::cout<<"~A()"<<std::endl;
    }
};

class B{
public:
    B(){
        std::cout<<"B()"<<std::endl;
    }
    ~B(){
        std::cout<<"~B()"<<std::endl;
    }
};

/*
class Test{
    A *pA{};
    B b{}; // this will be destroyed if exception is thrown bz it is 
    // a class on stack
    int *pInt{};
    char *pStr{};
    int *pArr{};
public:
    Test(){
        std::cout<<"Test(): Acquire resources"<<std::endl;
        pA = new A;
        pInt = new int;
        // throw a dummy exception here
        throw std::runtime_error("Dummy exception: failed to initialize resources");
        pStr = new char[1000];
        pArr = new int[50000];
        // if any allocation fails, exception will be thrown
        // and the destructor will not be called
        // and the resources will be leaked
        // so we need to handle the exception

        // so to solve such issues, we will use smart pointers, RAII concept.
    }
    ~Test(){
        std::cout<<"~Test(): Release resources"<<std::endl;
        delete pA;
        delete pInt;
        delete[] pStr;
        delete[] pArr;
    }
};
*/

class Test{
    std::unique_ptr<A> pA{}; // {} initializes the pointer to nullptr
    B b{}; // this will be destroyed if exception is thrown bz it is 
    // a class on stack
    std::unique_ptr<int> pInt{}; // initializes the pointer to nullptr
    std::string pStr{}; // initializes the string to empty
    std::vector<int> pArr{}; // initializes the vector to empty
public:
    Test(){
        std::cout<<"Test(): Acquire resources"<<std::endl;
        pA.reset(new A);
    }
    ~Test(){
        std::cout<<"~Test(): Release resources"<<std::endl;
    }
};

int main(){
    try{
        Test t;
    }catch(const std::runtime_error &e){
        std::cout<<"Caught exception: "<<e.what()<<std::endl;
    }
    std::cout<<"Program ended"<<std::endl;
    return 0;
}

/*
 * This is why if u use containers and smart pointers,
 * u dont need to worry about the resources being leaked
 * even if constructor or destructor throws an exception 
 * Note: the destructor should not throw an exception
 * if it does, it should be handled with the destructor itself.
 * If during stack unwinding, the destructor throws an exception,
 * the program will terminate.
 */