#include <iostream>

/*
 * Stream Inheritance Hierarchy:
 * 
 *                    ios_base
 *                       |
 *                    basic_ios
 *                    /      \
 *                   /        \
 *            istream        ostream
 *                   \        /
 *                    \      /
 *                   iostream
 * 
 * This is a classic diamond inheritance pattern.
 * The virtual inheritance is used to prevent multiple
 * copies of the base class (ios_base) in the derived class.
 */

class MyStream : public std::iostream {
public:
    MyStream() : std::iostream(nullptr) {
        std::cout << "MyStream constructor" << std::endl;
    }
    
    ~MyStream() {
        std::cout << "MyStream destructor" << std::endl;
    }
};

int main() {
    MyStream stream;
    
    // Demonstrate inheritance
    std::istream& is = stream;  // Can be used as istream
    std::ostream& os = stream;  // Can be used as ostream
    
    // Use stream for both input and output
    os << "Hello from ostream" << std::endl;
    
    return 0;
} 