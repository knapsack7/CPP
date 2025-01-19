#include <iostream>
#include <memory>
#include <string>

//Abstract Base Class for shape
class Shape {
public:
    virtual void draw() const = 0; //Pure Virtual Function
    virtual ~Shape() = default;
};

//Concrete Classes for Diff Shapes
class Circle : public Shape{
public:
    void draw() const override{
        std::cout<< "Drawing a Circle"<<std::endl;
    }
};

class Rectangle : public Shape{
public:
    void draw() const override{
        std::cout<< "Drawing a Rectangle"<<std::endl;
    }
};

class Triangle : public Shape{
public:
    void draw() const override{
        std::cout<< "Drawing a Triangle"<<std::endl;
    }
};


//Shape Factory Class
class ShapeFactory{
public:
    static std::shared_ptr<Shape> createShape(const std::string& shapeType){
        if (shapeType == "Circle"){
            return std::make_shared<Circle>();
        } else if (shapeType == "Rectangle"){
            return std::make_shared<Rectangle>();
        } else if (shapeType == "Triangle"){
            return std::make_shared<Triangle>();
        } else {
            throw std::invalid_argument("Unknown Shape Type");
        }
    }    
};

int main(){
    try{
        std::shared_ptr<Shape> shape1 = ShapeFactory::createShape("Circle");
        shape1->draw();

        std::shared_ptr<Shape> shape2 = ShapeFactory::createShape("Rectangle");
        shape2->draw();

        std::shared_ptr<Shape> shape3 = ShapeFactory::createShape("Triangle");
        shape3->draw();
    } catch(const std::exception& e){
        std::cerr << "Error: " << e.what() <<std::endl;
    }
}
