#include <iostream>

struct Resource
{
    Resource() = default;
    Resource(const Resource &other) { std::cout << "copy\n"; }
};

namespace URVO
{
    Resource getResource() {
        return Resource{}; // Unnamed RVO (pre C++17)
    }
} // namespace URVO

namespace NRVO
{
    Resource getResource()
    {
        Resource resource;
        return resource; // Named RVO
    }
} // namespace NRVO

int main()
{
    Resource resource1 = URVO::getResource();
    Resource resource2 = NRVO::getResource();
}
