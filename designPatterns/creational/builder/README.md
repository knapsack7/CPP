# Builder Design Pattern in C++

The **Builder Design Pattern** is a creational design pattern used to construct complex objects step by step. It separates the construction of an object from its representation, allowing the same construction process to create different representations.

---

## **Real-World Analogy**
Consider constructing a **house**. A house can have various configurations: a garden, a swimming pool, multiple floors, etc. The **Builder** separates the process of building the house from the actual representation of the house.

In a software project, an example could be creating a **complex HTTP request** with headers, body, query parameters, etc. The **Builder Pattern** can help assemble the request in a modular way.

---

## **Basic Example: Building a Car**

### **Scenario**
We want to create cars with different configurations, such as sports cars and SUVs. Each type of car requires different configurations for the engine, body, wheels, and additional features.

---

### **Code Example**

```cpp
#include <iostream>
#include <string>
#include <memory> // For smart pointers

// Step 1: Define the Product (Car)
class Car {
private:
    std::string engine;
    std::string body;
    int wheels;
    bool hasSunroof;

public:
    void setEngine(const std::string& engineType) { engine = engineType; }
    void setBody(const std::string& bodyType) { body = bodyType; }
    void setWheels(int numberOfWheels) { wheels = numberOfWheels; }
    void setSunroof(bool sunroof) { hasSunroof = sunroof; }

    void showDetails() const {
        std::cout << "Car Details:\n";
        std::cout << "Engine: " << engine << "\n";
        std::cout << "Body: " << body << "\n";
        std::cout << "Wheels: " << wheels << "\n";
        std::cout << "Sunroof: " << (hasSunroof ? "Yes" : "No") << "\n";
    }
};

// Step 2: Define the Abstract Builder
class CarBuilder {
public:
    virtual ~CarBuilder() = default;
    virtual void buildEngine() = 0;
    virtual void buildBody() = 0;
    virtual void buildWheels() = 0;
    virtual void buildSunroof() = 0;
    virtual std::shared_ptr<Car> getCar() = 0;
};

// Step 3: Create Concrete Builders
class SportsCarBuilder : public CarBuilder {
private:
    std::shared_ptr<Car> car;

public:
    SportsCarBuilder() { car = std::make_shared<Car>(); }
    void buildEngine() override { car->setEngine("V8 Engine"); }
    void buildBody() override { car->setBody("Sporty Body"); }
    void buildWheels() override { car->setWheels(4); }
    void buildSunroof() override { car->setSunroof(true); }
    std::shared_ptr<Car> getCar() override { return car; }
};

class SUVCarBuilder : public CarBuilder {
private:
    std::shared_ptr<Car> car;

public:
    SUVCarBuilder() { car = std::make_shared<Car>(); }
    void buildEngine() override { car->setEngine("V6 Engine"); }
    void buildBody() override { car->setBody("SUV Body"); }
    void buildWheels() override { car->setWheels(4); }
    void buildSunroof() override { car->setSunroof(false); }
    std::shared_ptr<Car> getCar() override { return car; }
};

// Step 4: Define the Director
class Director {
private:
    CarBuilder* builder;

public:
    void setBuilder(CarBuilder* newBuilder) { builder = newBuilder; }
    std::shared_ptr<Car> constructCar() {
        builder->buildEngine();
        builder->buildBody();
        builder->buildWheels();
        builder->buildSunroof();
        return builder->getCar();
    }
};

// Step 5: Client Code
int main() {
    Director director;

    // Build a sports car
    SportsCarBuilder sportsCarBuilder;
    director.setBuilder(&sportsCarBuilder);
    std::shared_ptr<Car> sportsCar = director.constructCar();
    sportsCar->showDetails();

    std::cout << "\n";

    // Build an SUV
    SUVCarBuilder suvCarBuilder;
    director.setBuilder(&suvCarBuilder);
    std::shared_ptr<Car> suvCar = director.constructCar();
    suvCar->showDetails();

    return 0;
}
```

---

## **How Does This Example Use the Builder Pattern?**
1. **Construction Steps Are Separated**:
   - The construction process (`buildEngine`, `buildBody`, etc.) is encapsulated in the builder classes.

2. **Client Does Not Manage Construction**:
   - The `Director` orchestrates the sequence of construction, keeping the client code simple.

3. **Different Representations**:
   - Multiple concrete builders (`SportsCarBuilder`, `SUVCarBuilder`) create different configurations of the car.

4. **Encapsulation of the Product**:
   - The `Car` class encapsulates the details of the final product, and the builder constructs it step-by-step.

---

## **Advantages**
1. **Step-by-Step Construction**:
   - Build complex objects incrementally.
2. **Different Representations**:
   - Easily create variations of a product using different builders.
3. **Improved Readability and Maintainability**:
   - The construction logic is separate from the client code.
4. **Encapsulation**:
   - The product-building process is encapsulated, reducing coupling.

---

## **Disadvantages**
1. **Increased Complexity**:
   - Additional classes and interfaces may add complexity.
2. **Overhead for Simple Objects**:
   - May not be worth it for simple objects that don’t require step-by-step construction.
3. **Dependency on Director**:
   - The construction process depends on the `Director`, which may not always be necessary.

---

## **When to Use the Builder Pattern**
- When constructing a complex object with many optional parts.
- When the construction process is highly customizable and needs to support different representations.
- When you want to ensure the construction process is consistent and encapsulated.

---

# Understanding the Use of `std::shared_ptr` in the Builder Design Pattern

In the context of the Builder Design Pattern, `std::shared_ptr` is used to manage the **lifetime of the object being built**. Here's an explanation of why `std::shared_ptr` is used and its significance, along with comparisons to alternatives.

---

## **Why Use `std::shared_ptr`?**

### 1. **Automatic Memory Management**
   - Objects like `Car` are dynamically allocated in the builder pattern.
   - `std::shared_ptr` ensures these objects are automatically deallocated when no longer needed, eliminating the risk of memory leaks.

### 2. **Shared Ownership**
   - `std::shared_ptr` allows **multiple components** to share ownership of the same object.
     - Example: The builder constructs the `Car` object and returns it to the client, which can safely use it without worrying about memory management.

### 3. **Safety Across Functions**
   - When a builder returns a `std::shared_ptr` object, the caller can safely store or use it without risking dangling pointers.

---

## **How `std::shared_ptr` Works in the Example**

### 1. **Creation in Builder**
   - The `Car` object is dynamically allocated and wrapped in a `std::shared_ptr`:
     ```cpp
     car = std::make_shared<Car>();
     ```

### 2. **Return from Builder**
   - The builder exposes the constructed object through its `getCar` method:
     ```cpp
     std::shared_ptr<Car> getCar() override { return car; }
     ```

### 3. **Usage in Director and Client**
   - The `Director` retrieves the object and passes it to the client:
     ```cpp
     std::shared_ptr<Car> sportsCar = director.constructCar();
     sportsCar->showDetails();
     ```
   - The `std::shared_ptr` ensures that the `Car` object is valid as long as it is needed.

---

## **Advantages of Using `std::shared_ptr`**

### 1. **Simplified Ownership Management**
   - The `Car` object is deallocated automatically when no longer referenced, avoiding manual memory management.

### 2. **Avoids Raw Pointers**
   - Raw pointers require explicit `delete`, which is error-prone and increases the risk of memory leaks or dangling pointers.

### 3. **Flexibility for Future Extensions**
   - If the project evolves to involve shared ownership of objects, `std::shared_ptr` naturally supports this.

---

## **Alternatives to `std::shared_ptr`**

### 1. **`std::unique_ptr`**
   - Ensures strict ownership semantics (only one owner at a time).
   - Suitable if no shared ownership is needed, but it requires transferring ownership using `std::move`:
     ```cpp
     std::unique_ptr<Car> getCar() {
         return std::move(car);
     }
     ```

### 2. **Raw Pointers**
   - Requires manual `delete` to avoid memory leaks.
   - Example:
     ```cpp
     Car* car = new Car();
     delete car;  // Manual cleanup required
     ```
   - **Not recommended** due to high error risk and complexity.

---

## **Why `std::shared_ptr` Is Preferred Here**
1. **Ease of Use**:
   - It simplifies memory management while allowing flexibility in object ownership.
2. **Safety**:
   - Prevents dangling pointers and memory leaks.
3. **Collaboration**:
   - Ensures the object remains valid as long as any part of the system needs it.

---

## **Conclusion**

In the Builder Design Pattern, `std::shared_ptr` is an ideal choice for managing the lifetime of dynamically allocated objects like the `Car`. It simplifies ownership, ensures safety, and allows for flexible usage in scenarios where the constructed object might be shared among multiple components. For stricter ownership, `std::unique_ptr` can be considered, but raw pointers should be avoided.



The **Builder Design Pattern** is a powerful tool for constructing complex objects step by step. In this example, we demonstrated how to use it to build cars with different configurations while keeping the construction process clean and flexible. This pattern is widely applicable in real-world scenarios such as creating configuration files, HTTP requests, or UI components.
