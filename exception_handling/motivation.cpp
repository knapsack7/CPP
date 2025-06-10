#include <iostream>
#include <limits>
using namespace std;

int processRecord(size_t count){
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


/*  
 * Exception handling
 * Mechanism to handle errors in programs that occur at runtime
 * These errors are called exceptions
 * Exist outside the normal functioning of the program
 * Require immediate handling by the program
 * If not handled, the program crashes
 * Cannot be ignored, unlike C error handling
 */

/*
 * Mechanism
 * try block
 *    creates a scope/block & exception causing appears here
 *    can contain other try-catch statements
 * throw
 *    throws an exception from the try block
 *    exception is object that is constructed in throw statement
 * catch
 *    handler that catches the exception object
 *    should appear just after the try block
 *    multiple catch blocks can exist
 */
int main(){
    try{
        processRecord(9);
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