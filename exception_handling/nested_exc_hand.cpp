#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <vector>
using namespace std;

class Test {
public:
    Test(){std::cout<<"Test(): Acquire resources"<<std::endl;}
    ~Test(){std::cout<<"~Test(): Release resources"<<std::endl;}
};


int processRecord(size_t count){
    std::unique_ptr<Test> t(new Test());
    
    if (count < 10)
        throw std::out_of_range("Count is too small");

    std::vector<int> p;
    p.reserve(count);
    std::vector<int> records;
    // processs the records
    for(int i = 0; i < count; i++){
        p.push_back(i);
    }
    std::default_random_engine eng;
    std::bernoulli_distribution dist;

    int errors{};

    for(int i = 0; i < count; ++i){
        try{
            std::cout << "Processing record #" << i << std::endl;
            if (!dist(eng)){ // returns boolean values
                errors++;
                throw std::runtime_error("could not processs the record");
            }
            std::cout << std::endl;
        }catch( std::runtime_error &e){
            std::cout << "[ERROR : Caught exception: " << e.what() << "]" << std::endl;
            if (errors > 4){
                std::runtime_error err("Too many errors : Abonding operation");
                e = err;
                throw;
            }
        }
    }
    return 0;
}


int main(){
    try{
        processRecord(15);
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