#include<iostream>
using namespace std;

class Point {
public:
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Add a less-than comparison operator for sorting
    bool operator<(const Point& other) const {
        // Sort first by x-coordinate, then by y-coordinate
        return x+y <  other.x + other.y;
    }
    // Add a greater-than comparison operator for sorting
    bool operator>(const Point& other) const {
        // Sort first by x-coordinate, then by y-coordinate
        return x+y >  other.x + other.y;
    }
};



int main() {
    std::vector<Point> vec{{2,3}, {6, 4}, {9,10}};
    //sort(vec.begin(), vec.end(), greater<>());
    sort(vec.begin(), vec.end(), [](Point a, Point b){return a.x + a.y < b.x + b.y;});
    for (auto ele : vec)
        cout<<ele.x<<"--"<<ele.y<<endl;
    return 0;
}