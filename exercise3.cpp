#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{ rd() };

    std::uniform_int_distribution<int> int_dist{ 0, 10 };
    std::uniform_real_distribution<double> float_dist{ 0.0, 100.0 };

    std::cout << "10 random integers between 0 and 10:\n";
    for (int i = 0; i < 10; ++i)
    {
        std::cout << int_dist(gen) << '\n';
    }

    std::cout << "\n5 random floating-point numbers between 0 and 100:\n";
    for (int i = 0; i < 5; ++i)
    {
        std::cout << float_dist(gen) << '\n';
    }

    return 0;
}
