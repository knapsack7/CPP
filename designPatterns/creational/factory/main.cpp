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

enum class ObjectType {CIRCLE, RECTANGLE, TRIANGLE};

//Shape Factory Class
class ShapeFactory{
public:
    static std::shared_ptr<Shape> createShape(const ObjectType shapeType){
        if (shapeType == ObjectType::CIRCLE){
            circles++;
            return std::make_shared<Circle>();
        } else if (shapeType == ObjectType::RECTANGLE){
            rectangles++;
            return std::make_shared<Rectangle>();
        } else if (shapeType == ObjectType::TRIANGLE){
            triangles++;
            return std::make_shared<Triangle>();
        } else {
            throw std::invalid_argument("Unknown Shape Type");
        }
    }

    static void printCounts(){
        std::cout<<"Circles : " << circles <<std::endl;
        std::cout<<"Rectaangles : " << rectangles <<std::endl; 
        std::cout<<"Triangles: " << triangles <<std::endl; 
    }
private:
    ShapeFactory(const ShapeFactory&) = delete;
    ShapeFactory& operator=(const ShapeFactory&) = delete;
    static int circles, rectangles, triangles;
};

int ShapeFactory::circles = 0;
int ShapeFactory::rectangles = 0;
int ShapeFactory::triangles = 0;

int main(){
    try{
        std::shared_ptr<Shape> shape1 = ShapeFactory::createShape(ObjectType::CIRCLE);
        shape1->draw();

        std::shared_ptr<Shape> shape2 = ShapeFactory::createShape(ObjectType::RECTANGLE);
        shape2->draw();

        std::shared_ptr<Shape> shape3 = ShapeFactory::createShape(ObjectType::TRIANGLE);
        shape3->draw();
    } catch(const std::exception& e){
        std::cerr << "Error: " << e.what() <<std::endl;
    }
    std::cout<<"Total Objects info : "<<std::endl;
    ShapeFactory::printCounts();
    return 0;
}
