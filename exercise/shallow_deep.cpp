#include <iostream>
#include <cstring>
#include <memory>
#include <vector>

// Safe demonstration of shallow vs deep copy concepts
class SafeString {
private:
    char* data;
    size_t length;
    
public:
    // Constructor
    SafeString(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        std::cout << "SafeString: Allocated memory for '" << str << "'" << std::endl;
    }
    
    // Destructor
    ~SafeString() {
        delete[] data;
        std::cout << "SafeString: Freed memory for '" << data << "'" << std::endl;
    }
    
    // Getter
    const char* getData() const { return data; }
    
    // Setter
    void setData(const char* str) {
        delete[] data;
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
};

// Class demonstrating shallow copy problems (safely)
class ShallowCopyDemo {
private:
    SafeString* strPtr;
    bool isOwner; // Track ownership to prevent double deletion
    
public:
    // Constructor
    ShallowCopyDemo(const char* str) {
        strPtr = new SafeString(str);
        isOwner = true;
        std::cout << "ShallowCopyDemo: Created object with '" << str << "'" << std::endl;
    }
    
    // Shallow copy constructor
    ShallowCopyDemo(const ShallowCopyDemo& other) {
        strPtr = other.strPtr; // Just copy the pointer - SHALLOW!
        isOwner = false; // Don't own the memory
        std::cout << "ShallowCopyDemo: Copy constructor - SHALLOW COPY!" << std::endl;
    }
    
    // Destructor
    ~ShallowCopyDemo() {
        if (isOwner) {
            delete strPtr;
            std::cout << "ShallowCopyDemo: Destructor called (owner)" << std::endl;
        } else {
            std::cout << "ShallowCopyDemo: Destructor called (non-owner)" << std::endl;
        }
    }
    
    // Getter
    const char* getString() const { return strPtr->getData(); }
    
    // Setter
    void setString(const char* str) { strPtr->setData(str); }
};

// Class demonstrating deep copy benefits
class DeepCopyDemo {
private:
    SafeString* strPtr;
    
public:
    // Constructor
    DeepCopyDemo(const char* str) {
        strPtr = new SafeString(str);
        std::cout << "DeepCopyDemo: Created object with '" << str << "'" << std::endl;
    }
    
    // Deep copy constructor
    DeepCopyDemo(const DeepCopyDemo& other) {
        strPtr = new SafeString(other.strPtr->getData()); // Create new object - DEEP!
        std::cout << "DeepCopyDemo: Copy constructor - DEEP COPY!" << std::endl;
    }
    
    // Destructor
    ~DeepCopyDemo() {
        delete strPtr;
        std::cout << "DeepCopyDemo: Destructor called" << std::endl;
    }
    
    // Getter
    const char* getString() const { return strPtr->getData(); }
    
    // Setter
    void setString(const char* str) { strPtr->setData(str); }
};

// Function to demonstrate shallow copy problems safely
void demonstrateShallowCopyProblems() {
    std::cout << "\n=== Shallow Copy Problems (Safe Demo) ===" << std::endl;
    
    std::cout << "Creating original ShallowCopyDemo object..." << std::endl;
    ShallowCopyDemo original("Hello");
    
    std::cout << "\nCreating copy using copy constructor..." << std::endl;
    ShallowCopyDemo copy = original; // Shallow copy!
    
    std::cout << "\nOriginal string: " << original.getString() << std::endl;
    std::cout << "Copy string: " << copy.getString() << std::endl;
    
    std::cout << "\nModifying copy..." << std::endl;
    copy.setString("Modified");
    
    std::cout << "Original string: " << original.getString() << std::endl;
    std::cout << "Copy string: " << copy.getString() << std::endl;
    
    std::cout << "\nPROBLEM: Both objects point to the same memory!" << std::endl;
    std::cout << "Modifying one affects the other!" << std::endl;
    
    std::cout << "\nAbout to destroy objects (safe cleanup with ownership tracking)..." << std::endl;
}

// Function to demonstrate deep copy benefits
void demonstrateDeepCopyBenefits() {
    std::cout << "\n=== Deep Copy Benefits ===" << std::endl;
    
    std::cout << "Creating original DeepCopyDemo object..." << std::endl;
    DeepCopyDemo original("Hello");
    
    std::cout << "\nCreating copy using copy constructor..." << std::endl;
    DeepCopyDemo copy = original; // Deep copy!
    
    std::cout << "\nOriginal string: " << original.getString() << std::endl;
    std::cout << "Copy string: " << copy.getString() << std::endl;
    
    std::cout << "\nModifying copy..." << std::endl;
    copy.setString("Modified");
    
    std::cout << "Original string: " << original.getString() << std::endl;
    std::cout << "Copy string: " << copy.getString() << std::endl;
    
    std::cout << "\nBENEFIT: Each object has its own memory!" << std::endl;
    std::cout << "Modifying one doesn't affect the other!" << std::endl;
    
    std::cout << "\nAbout to destroy objects (safe cleanup)..." << std::endl;
}

// Function to demonstrate modern C++ solutions
void demonstrateModernCppSolutions() {
    std::cout << "\n=== Modern C++ Solutions ===" << std::endl;
    
    std::cout << "1. Using std::string (automatic deep copy):" << std::endl;
    {
        std::string str1 = "Hello";
        std::string str2 = str1; // Automatic deep copy
        
        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str2: " << str2 << std::endl;
        
        str2 = "Modified";
        std::cout << "After modification:" << std::endl;
        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str2: " << str2 << std::endl;
    }
    
    std::cout << "\n2. Using std::vector (automatic deep copy):" << std::endl;
    {
        std::vector<int> vec1 = {1, 2, 3, 4, 5};
        std::vector<int> vec2 = vec1; // Automatic deep copy
        
        std::cout << "vec1: ";
        for (int x : vec1) std::cout << x << " ";
        std::cout << std::endl;
        
        std::cout << "vec2: ";
        for (int x : vec2) std::cout << x << " ";
        std::cout << std::endl;
        
        vec2[0] = 100;
        std::cout << "After modifying vec2[0] = 100:" << std::endl;
        std::cout << "vec1: ";
        for (int x : vec1) std::cout << x << " ";
        std::cout << std::endl;
        
        std::cout << "vec2: ";
        for (int x : vec2) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    std::cout << "\n3. Using smart pointers:" << std::endl;
    {
        auto ptr1 = std::make_unique<std::string>("Hello");
        // auto ptr2 = ptr1; // Won't compile - unique_ptr is move-only
        
        auto ptr2 = std::make_unique<std::string>(*ptr1); // Explicit deep copy
        std::cout << "ptr1: " << *ptr1 << std::endl;
        std::cout << "ptr2: " << *ptr2 << std::endl;
        
        *ptr2 = "Modified";
        std::cout << "After modification:" << std::endl;
        std::cout << "ptr1: " << *ptr1 << std::endl;
        std::cout << "ptr2: " << *ptr2 << std::endl;
    }
    
    std::cout << "\n4. Using shared_ptr (reference counting):" << std::endl;
    {
        auto shared1 = std::make_shared<std::string>("Shared");
        auto shared2 = shared1; // Shared ownership (not deep copy)
        
        std::cout << "shared1: " << *shared1 << std::endl;
        std::cout << "shared2: " << *shared2 << std::endl;
        std::cout << "Reference count: " << shared1.use_count() << std::endl;
        
        *shared2 = "Modified";
        std::cout << "After modification:" << std::endl;
        std::cout << "shared1: " << *shared1 << std::endl;
        std::cout << "shared2: " << *shared2 << std::endl;
        std::cout << "Both point to same memory (shared ownership)" << std::endl;
    }
}

// Function to demonstrate copy elision and move semantics
void demonstrateCopyElisionAndMove() {
    std::cout << "\n=== Copy Elision and Move Semantics ===" << std::endl;
    
    std::cout << "Copy Elision (compiler optimization):" << std::endl;
    {
        // Modern compilers can elide copies
        DeepCopyDemo obj = DeepCopyDemo("Temporary"); // Copy elision possible
        std::cout << "obj: " << obj.getString() << std::endl;
    }
    
    std::cout << "\nMove Semantics (C++11):" << std::endl;
    {
        std::string str1 = "Original";
        std::string str2 = std::move(str1); // Move constructor
        
        std::cout << "str1: '" << str1 << "' (moved from - empty)" << std::endl;
        std::cout << "str2: '" << str2 << "' (moved to)" << std::endl;
    }
    
    std::cout << "\nMove with unique_ptr:" << std::endl;
    {
        auto ptr1 = std::make_unique<std::string>("Unique");
        auto ptr2 = std::move(ptr1); // Transfer ownership
        
        std::cout << "ptr1: " << (ptr1 ? *ptr1 : "nullptr") << std::endl;
        std::cout << "ptr2: " << *ptr2 << std::endl;
    }
}

// Function to demonstrate when to use each
void demonstrateWhenToUseEach() {
    std::cout << "\n=== When to Use Shallow vs Deep Copy ===" << std::endl;
    
    std::cout << "Use SHALLOW COPY when:" << std::endl;
    std::cout << "1. Object contains only simple data types (int, double, etc.)" << std::endl;
    std::cout << "2. Object is immutable (read-only)" << std::endl;
    std::cout << "3. Object is small and copying is expensive" << std::endl;
    std::cout << "4. You want to share data between objects" << std::endl;
    std::cout << "5. Using reference counting (shared_ptr)" << std::endl;
    
    std::cout << "\nUse DEEP COPY when:" << std::endl;
    std::cout << "1. Object contains pointers to dynamic memory" << std::endl;
    std::cout << "2. Object needs to be modified independently" << std::endl;
    std::cout << "3. Object owns resources that need cleanup" << std::endl;
    std::cout << "4. You want to prevent double deletion" << std::endl;
    std::cout << "5. Object contains file handles, network connections" << std::endl;
    
    std::cout << "\nUse MOVE SEMANTICS when:" << std::endl;
    std::cout << "1. Object is expensive to copy" << std::endl;
    std::cout << "2. Object is temporary or about to be destroyed" << std::endl;
    std::cout << "3. You want to transfer ownership" << std::endl;
    std::cout << "4. Returning large objects from functions" << std::endl;
}

// Function to demonstrate common pitfalls
void demonstrateCommonPitfalls() {
    std::cout << "\n=== Common Pitfalls ===" << std::endl;
    
    std::cout << "1. Double Deletion (shallow copy):" << std::endl;
    std::cout << "   - Two objects point to same memory" << std::endl;
    std::cout << "   - Both try to delete the same memory" << std::endl;
    std::cout << "   - Results in undefined behavior" << std::endl;
    
    std::cout << "\n2. Dangling Pointers (shallow copy):" << std::endl;
    std::cout << "   - One object deletes shared memory" << std::endl;
    std::cout << "   - Other object still points to deleted memory" << std::endl;
    std::cout << "   - Accessing it causes undefined behavior" << std::endl;
    
    std::cout << "\n3. Memory Leaks (incomplete deep copy):" << std::endl;
    std::cout << "   - Forgetting to delete old memory in assignment" << std::endl;
    std::cout << "   - Not implementing copy assignment operator" << std::endl;
    
    std::cout << "\n4. Self-Assignment:" << std::endl;
    std::cout << "   - obj = obj; can cause problems" << std::endl;
    std::cout << "   - Need to check for self-assignment" << std::endl;
    
    std::cout << "\n5. Inconsistent Copy Semantics:" << std::endl;
    std::cout << "   - Having copy constructor but no assignment operator" << std::endl;
    std::cout << "   - Or vice versa" << std::endl;
}

// Function to demonstrate Rule of Three/Five
void demonstrateRuleOfThree() {
    std::cout << "\n=== Rule of Three/Five ===" << std::endl;
    
    std::cout << "Rule of Three (C++98):" << std::endl;
    std::cout << "If you define any of these, define all three:" << std::endl;
    std::cout << "1. Destructor" << std::endl;
    std::cout << "2. Copy Constructor" << std::endl;
    std::cout << "3. Copy Assignment Operator" << std::endl;
    
    std::cout << "\nRule of Five (C++11):" << std::endl;
    std::cout << "If you define any of these, define all five:" << std::endl;
    std::cout << "1. Destructor" << std::endl;
    std::cout << "2. Copy Constructor" << std::endl;
    std::cout << "3. Copy Assignment Operator" << std::endl;
    std::cout << "4. Move Constructor" << std::endl;
    std::cout << "5. Move Assignment Operator" << std::endl;
    
    std::cout << "\nModern C++ (Rule of Zero):" << std::endl;
    std::cout << "Prefer to use RAII and smart pointers" << std::endl;
    std::cout << "Let the compiler generate everything automatically" << std::endl;
}

int main() {
    std::cout << "Shallow vs Deep Copy - Safe Demonstration" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    demonstrateShallowCopyProblems();
    demonstrateDeepCopyBenefits();
    demonstrateModernCppSolutions();
    demonstrateCopyElisionAndMove();
    demonstrateWhenToUseEach();
    demonstrateCommonPitfalls();
    demonstrateRuleOfThree();
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Shallow Copy:" << std::endl;
    std::cout << "- Copies only the pointer/reference" << std::endl;
    std::cout << "- Multiple objects share the same data" << std::endl;
    std::cout << "- Can cause double deletion and dangling pointers" << std::endl;
    std::cout << "- Faster but dangerous with dynamic memory" << std::endl;
    
    std::cout << "\nDeep Copy:" << std::endl;
    std::cout << "- Creates a complete copy of the data" << std::endl;
    std::cout << "- Each object has its own independent data" << std::endl;
    std::cout << "- Safe but potentially slower" << std::endl;
    std::cout << "- Prevents memory management issues" << std::endl;
    
    std::cout << "\n=== For NetApp/Storage Systems ===" << std::endl;
    std::cout << "1. Use deep copy for file handles and buffers" << std::endl;
    std::cout << "2. Use shallow copy for immutable metadata" << std::endl;
    std::cout << "3. Use move semantics for large data transfers" << std::endl;
    std::cout << "4. Always implement proper copy semantics" << std::endl;
    std::cout << "5. Use smart pointers to avoid manual memory management" << std::endl;
    std::cout << "6. Use std::string, std::vector for automatic deep copy" << std::endl;
    
    return 0;
} 