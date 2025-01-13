#include <iostream>

struct Degrees
{
    Degrees() : degrees_(0)
    {
        std::cout << "Default constructed\n";
    }
    Degrees(double degrees) : degrees_(degrees)
    {
        std::cout << "Constructed with " << degrees_ << "\n";
    }
    double degrees_;
};

struct Position
{
    Position() { longitude = Degrees{2}; }
    Degrees latitude{1}; // Default member initializer
    Degrees longitude;
};

int main()
{
    Position position;
}
