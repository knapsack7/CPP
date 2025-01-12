#include <iostream>
#include <vector>

struct MemoryArea
{
    MemoryArea(int number) : number_(number) {}
    ~MemoryArea() { std::cout << "Freed memory area " << number_ << std::endl; }

    int number_;
};

class MemoryAreaContainer
{
  public:
    MemoryAreaContainer();
    std::vector<MemoryArea> &getMemoryAreas()
    {
        return memoryAreas_;
    }

  private:
    std::vector<MemoryArea> memoryAreas_;
};

MemoryAreaContainer::MemoryAreaContainer()
    : memoryAreas_{MemoryArea{1}, MemoryArea{2}}
{
}

int main()
{
    for (const auto &lp : MemoryAreaContainer{}.getMemoryAreas())
    {
        std::cout << lp.number_ << std::endl;
    }
}
