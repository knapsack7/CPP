#include <iostream>
#include <thread>
/*

Let me explain the memory model for threads in detail:
Thread Stack Memory:
Each thread gets its own stack memory
Stack memory is private to each thread
Default stack size is typically 1-8 MB (varies by OS)
Local variables, function parameters, and return addresses are stored here
In your code, the print() and print1() functions' local variables would be on their respective thread stacks
Heap Memory:
Heap memory is shared between all threads in a process
All threads can access the same heap memory
In your code, the thread objects are allocated on the heap using new
This is why you need synchronization mechanisms (mutex, locks) when accessing shared heap memory
What's Shared vs Not Shared:
Shared Memory:
Heap memory (allocated with new, malloc)
Global variables
Static variables
File descriptors
Process resources (like open files, sockets)
Not Shared (Private to each thread):
Stack memory
Thread-local storage (variables marked with thread_local)
CPU registers
Thread-specific data
 
Important Considerations:
When threads access shared memory, you need synchronization
Stack memory is limited, so don't allocate large objects on stack
Heap memory is shared but requires manual management
Thread-local storage is useful for thread-specific data
Global variables should be used carefully as they're shared

Best Practices:
Use thread-local storage for thread-specific data
Use mutexes or other synchronization mechanisms for shared memory
Be careful with global variables
Consider using smart pointers for heap memory management
Be aware of stack size limitations


*/

// Shared memory
int globalVar = 0;  // Shared between all threads
static int staticVar = 0;  // Shared between all threads

void threadFunction() {
    // Private to each thread
    int localVar = 0;  // On thread's stack
    
    // Shared memory
    globalVar++;  // Accessing shared memory
    staticVar++;  // Accessing shared memory
    
    // Thread-local storage
    thread_local int threadLocalVar = 0;  // Private to this thread
    threadLocalVar++;
}

int main() {
    // Shared heap memory
    int* heapVar = new int(0);  // Shared between all threads
    
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    
    t1.join();
    t2.join();
    
    delete heapVar;
    return 0;
}