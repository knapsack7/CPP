#include <iostream>
#include <ostream>
#include <string>
#include <thread>

namespace {

constexpr const char* kNames[] = {"Abdul", "Bart", "Claudia", "Divya"};
constexpr std::size_t kNumChildren = sizeof(kNames) / sizeof(kNames[0]);

std::string word_for(int n)
{
    const bool by3 = (n % 3 == 0);
    const bool by5 = (n % 5 == 0);
    if (by3 && by5)
    {
        return "fizzbuzz!";
    }
    if (by3)
    {
        return "fizz!";
    }
    if (by5)
    {
        return "buzz!";
    }
    return std::to_string(n);
}

} // namespace

// Prints one line per count: "<Name> says <number or fizz/buzz/...>".
void play_fizzbuzz_circle(std::ostream& out, int last_number)
{
    for (int n = 1; n <= last_number; ++n)
    {
        const char* speaker = kNames[(n - 1) % kNumChildren];
        out << speaker << " says " << word_for(n) << '\n';
    }
}

int main()
{
    constexpr int kRounds = 20;

    std::thread game([&] { play_fizzbuzz_circle(std::cout, kRounds); });
    game.join();

    return 0;
}
