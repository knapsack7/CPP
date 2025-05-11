#include<iostream>
using namespace std;
#include<memory>
#include<vector>

/*
 *  Case                                                    Do you need to write ur own destructor?
 *  Using only STL containers, smart pointers, RAII         No need, compiler-generated is fine
 *  Using raw new/malloc, or custom handles                 Yes, write destructor to clean up
 *  Base class in polymorphic hierarchy                     Must have a virtual ~BASE()
 *  Derived class, no extra cleanup                         Let compiler generate destructor
 */


class Shape{
public:
    virtual int area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape{
    const float pi = 3.14f;
    const int rad = 0;
public:
    Circle(int rad) : rad(rad){}; 
    int area() const override{
        return static_cast<int>(pi * rad * rad);
    }
    ~Circle(){};
};

class Rectangle : public Shape{
    const int len = 0;
    const int breadth = 0;
public:
    Rectangle(int l, int b) : len(l), breadth(b){}; 
    int area() const override{
        return len * breadth;
    }
    ~Rectangle(){};
};

int main(){
    std::vector<std::unique_ptr<Shape>> shape_objs;
    shape_objs.push_back(std::make_unique<Circle>(4));
    shape_objs.push_back(std::make_unique<Rectangle>(2,4));
    std::cout<< shape_objs[0]->area();
    std::cout<<endl<<shape_objs[1]->area();
    return 0;
}