#include <iostream>

enum class Color{
    RED,
    GREEN,
    BLUE
};

/*
-Type created through enum keyword
-created with restricted range of values, called symbolic
constants or enumerators
-Enumerators are internally represented as undefined integral types
-can implicitly convert to an integer, but not the other way around
-default value starts from 0, but users can assign any value
-enum class is a scoped enum, which means that the enumerators
are not in the global namespace
enum Color(Red, Green, Blue);
Color c = Red;
c =1; // Compile error, use static_cast to convert
int x = Green; // x will contain 1
*/

enum class TrafficLight : char{
    RED = 'R',
    GREEN,
    YELLOW
};

void FillColor(Color color){
    // Fill background with the color
    if (color == Color::RED){
        std::cout << "Red" << std::endl;
    }
    else if (color == Color::GREEN){
        std::cout << "Green" << std::endl;
    }
    else if (color == Color::BLUE){
        std::cout << "Blue" << std::endl;
    }
}

int main(){
    Color c = Color::RED;
    FillColor(c);
    FillColor(Color::GREEN);
    FillColor(static_cast<Color>(TrafficLight::RED));
    FillColor(static_cast<Color>(2));
    // int x = Color::RED; // Error
    int x = static_cast<int>(Color::RED);
    return 0;
}