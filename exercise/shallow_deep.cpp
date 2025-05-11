#include <iostream>
#include <vector>

class Log {
    int log_daemon_id;
    std::vector<int> space;  // RAII-managed dynamic array
public:
    // Constructor
    Log(int id, int sz) : log_daemon_id(id), space(sz) {
        for (int i = 0; i < sz; ++i) {
            space[i] = i;  // initializing with sample values
        }
    }

    // Deep Copy Constructor
    Log(const Log& obj) 
        : log_daemon_id(obj.log_daemon_id), space(obj.space) {}  // std::vector handles deep copy

    // Copy Assignment Operator (deep copy)
    Log& operator=(const Log& obj) {
        if (this != &obj) {
            log_daemon_id = obj.log_daemon_id;
            space = obj.space;  // std::vector deep copies here too
        }
        return *this;
    }

    // Destructor — not needed explicitly since vector handles memory
    // ~Log() = default;

    friend void printMembers(const Log& obj);
};

void printMembers(const Log& obj) {
    std::cout << "log_daemon_id: " << obj.log_daemon_id 
              << " sz: " << obj.space.size() 
              << " values: ";
    for (auto val : obj.space) std::cout << val << " ";
    std::cout << "\n";
}

int main() {
    Log obj1(1, 10);        // Constructor
    Log obj2 = obj1;        // Copy constructor
    Log obj3(2, 5);
    obj3 = obj1;            // Copy assignment

    printMembers(obj1);
    printMembers(obj2);
    printMembers(obj3);

    return 0;
}
