#include <iostream>
#include <string>

/*
 * Key Points about Abstract Classes:
 * 1. Must have at least one pure virtual function
 * 2. Cannot be instantiated directly
 * 3. Derived classes must implement all pure virtual functions
 * 4. Can have both virtual and non-virtual functions
 * 5. Can have constructors and destructors
 * 6. Can have member variables
 */

// Abstract base class
class Shape {
protected:
    std::string name;
    double area;

public:
    // Constructor
    Shape(const std::string& n) : name(n), area(0) {
        std::cout << "Shape constructor called" << std::endl;
    }

    // Virtual destructor (important for proper cleanup)
    virtual ~Shape() {
        std::cout << "Shape destructor called" << std::endl;
    }

    // Pure virtual function - makes the class abstract
    virtual double calculateArea() = 0;

    // Regular virtual function - can be overridden
    virtual void display() {
        std::cout << "Shape: " << name << std::endl;
    }

    // Non-virtual function - cannot be overridden
    void setArea(double a) {
        area = a;
    }

    // Pure virtual function
    virtual void draw() = 0;
};

// Concrete derived class
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {
        calculateArea(); // Calculate area in constructor
    }

    // Must implement all pure virtual functions
    double calculateArea() override {
        area = 3.14159 * radius * radius;
        return area;
    }

    void draw() override {
        std::cout << "Drawing a circle with radius " << radius << std::endl;
    }

    // Override virtual function
    void display() override {
        std::cout << "Circle with radius: " << radius << std::endl;
        std::cout << "Area: " << area << std::endl;
    }
};

// Another concrete derived class
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) 
        : Shape("Rectangle"), width(w), height(h) {
        calculateArea();
    }

    double calculateArea() override {
        area = width * height;
        return area;
    }

    void draw() override {
        std::cout << "Drawing a rectangle " << width << "x" << height << std::endl;
    }
};

int main() {
    // Shape s;  // Error: Cannot instantiate abstract class
    
    Circle c(5);
    c.display();
    c.draw();

    Rectangle r(4, 6);
    r.display();
    r.draw();

    // Using polymorphism
    Shape* shapes[] = {&c, &r};
    for (Shape* shape : shapes) {
        shape->display();
        shape->draw();
    }

    return 0;
} 