#include <iostream>
#include <thread>

class MyClass {
public:
    void printMessage(int id) {
        std::cout << "Thread ID: " << id << ", Object Address: " << this << std::endl;
    }

    void startThread() {
        std::thread t(&MyClass::printMessage, this, 42); // Pass 'this' to call printMessage
        t.join();
    }
};

int main() {
    MyClass obj;
    obj.startThread();
    return 0;
}
