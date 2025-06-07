#include <iostream>
#include <memory>

class Point{
    int m_x{};
    int m_y{};
public:
    Point(int x, int y) : m_x(x), m_y(y){
        std::cout<< "Point(" << m_x << ", " << m_y << ")" << std::endl;
    }
    void show() const{
        std::cout<< "Point(" << m_x << ", " << m_y << ")" << std::endl;
    }
};

int main(){
    //std::shared_ptr<int> p1{new int{10}};
    auto p = std::make_unique<int>(5);
    std::cout<< "p : " << *p << std::endl;
    auto pt = std::make_unique<Point>(3,5);

    auto pArr = std::make_unique<int[]>(5);
    pArr[0] = 10;

    // Note: With make_shared u cant use custom deleter

    auto p1 = std::make_shared<int>(5);
    std::cout<< "p : " << *p << std::endl;
    auto pt1 = std::make_shared<Point>(3,5);


    // There is no way to use
    // std::make_shared directly with array types like int[]. 
    // auto pArr1 = std::make_shared<int[]>(5);
    //pArr1[0] = 10;
    return 0;
}