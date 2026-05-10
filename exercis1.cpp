#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers{4, 2, 3, 5, 1};

    for (auto value : numbers) {
        std::cout << value << " ";
    }
    std::cout << '\n';

    for (auto& value : numbers) {
        value += 2;
    }

    for (auto value : numbers) {
        std::cout << value << " ";
    }
    std::cout << '\n';

    return 0;
}
