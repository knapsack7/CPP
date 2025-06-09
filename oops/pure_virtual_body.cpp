#include <iostream>

class Abstract {
public:
    // Pure virtual function declaration
    virtual void mustImplement() = 0;
    
    // Pure virtual function declaration
    virtual void canOverride() = 0;
    
    // Implementation of canOverride
    void canOverrideImpl() {
        std::cout << "Abstract::canOverride default implementation" << std::endl;
    }
    
    virtual ~Abstract() {}
};

// Implementation of pure virtual function
void Abstract::canOverride() {
    std::cout << "Abstract::canOverride default implementation" << std::endl;
}

class Concrete : public Abstract {
public:
    // Must implement this - no default implementation
    void mustImplement() override {
        std::cout << "Concrete::mustImplement" << std::endl;
    }
    
    // Can use default implementation or override
    void canOverride() override {
        // Using base implementation
        Abstract::canOverride();
        std::cout << "Concrete::canOverride" << std::endl;
    }
};

int main() {
    Concrete c;
    c.mustImplement();  // Calls Concrete implementation
    c.canOverride();    // Calls Concrete implementation which uses base implementation
    
    return 0;
} 