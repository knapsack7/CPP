#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <random>

/*
 * Parallel STL Algorithms
 * May STL algo by default execute serially
 * C++17 provides overloads to these algorithms that can now execute parallely
 * Algorithms that can be parallelized accept a new template parameter called execution policy
 *    - used to disambiguate the calls to overloads of the algorithm
 * This can be used to inform the algorithm if it should execute serially or parallelly
 * The internal implementation details are hidden to the user
 */


class Timer{
    std::chrono::steady_clock::time_point m_start;
public:
    Timer(): m_start(std::chrono::steady_clock::now()){}

    void showResult(std::string_view msg = ""){
        auto end = std::chrono::steady_clock::now();
        auto diff = end - m_start;
        std::cout << msg << " took " << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ms" << std::endl;
    }
};

constexpr unsigned VEC_SIZE{1000000};

std::vector<long> createVector(){
    std::vector<long> v;
    v.reserve(VEC_SIZE);
    std::default_random_engine eng(std::random_device{}());
    std::uniform_int_distribution<long> dist{0, VEC_SIZE};
    for(unsigned i = 0; i < VEC_SIZE; ++i){
        v.push_back(dist(eng));
    }
    return v;
}
int main() {
    auto dataset = createVector();
    Timer t;
    std::sort(dataset.begin(), dataset.end());
    t.showResult("Serial sort");
    std::sort(std::execution::par, dataset.begin(), dataset.end());
    t.showResult("Serial sort");
   return 0;
}