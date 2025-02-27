#include <iostream>
#include <memory>
#include <unordered_map>

// Step 1: Abstract Base Prototype Class
class Prototype {
public:
    virtual std::shared_ptr<Prototype> clone() const = 0; // Clone method
    virtual void show() const = 0; // Display object details
    virtual ~Prototype() = default; // Default virtual destructor
};

// Step 2: Concrete Prototype A
class ConcretePrototypeA : public Prototype {
private:
    int value;
public:
    explicit ConcretePrototypeA(int val) : value(val) {}

    // Clone method using move semantics
    std::shared_ptr<Prototype> clone() const override {
        return std::make_shared<ConcretePrototypeA>(*this);
    }

    void show() const override {
        std::cout << "ConcretePrototypeA with value: " << value << std::endl;
    }
};

// Step 3: Concrete Prototype B
class ConcretePrototypeB : public Prototype {
private:
    std::string name;
public:
    explicit ConcretePrototypeB(std::string n) : name(std::move(n)) {}

    std::shared_ptr<Prototype> clone() const override {
        return std::make_shared<ConcretePrototypeB>(*this);
    }

    void show() const override {
        std::cout << "ConcretePrototypeB with name: " << name << std::endl;
    }
};

// Step 4: Optimized Prototype Registry
class PrototypeRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<Prototype>> prototypes;
public:
    void registerPrototype(const std::string& key, std::shared_ptr<Prototype> prototype) {
        prototypes.emplace(key, std::move(prototype));
    }

    std::shared_ptr<Prototype> createPrototype(const std::string& key) const {
        auto it = prototypes.find(key);
        return (it != prototypes.end()) ? it->second->clone() : nullptr;
    }
};

// Step 5: Main function to test the optimized prototype pattern
int main() {
    PrototypeRegistry registry;

    // Register prototypes
    registry.registerPrototype("A", std::make_shared<ConcretePrototypeA>(100));
    registry.registerPrototype("B", std::make_shared<ConcretePrototypeB>("Optimized PrototypeB"));

    // Create clones
    auto clonedA = registry.createPrototype("A");
    auto clonedB = registry.createPrototype("B");

    // Display cloned objects
    if (clonedA) clonedA->show();
    if (clonedB) clonedB->show();

    return 0;
}
