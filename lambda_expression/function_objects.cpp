#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

// Function Objects (Functors)
template<typename T>
struct MaxFunctor {
    T operator()(T a, T b) const {
        return a > b ? a : b;
    }
};

template<typename T>
struct GreaterFunctor {
    bool operator()(T a, T b) const {
        return a > b;
    }
};

template<typename T>
struct LessFunctor {
    bool operator()(T a, T b) const {
        return a < b;
    }
};

template<typename T>
struct MinMaxFunctor {
    std::pair<T, T> operator()(typename std::vector<T>::iterator begin, 
                              typename std::vector<T>::iterator end) const {
        if (begin == end) return {T(), T()};
        T min_val = *begin;
        T max_val = *begin;
        for (auto it = begin; it != end; ++it) {
            if (*it < min_val) min_val = *it;
            if (*it > max_val) max_val = *it;
        }
        return {min_val, max_val};
    }
};

int main() {
    // Lambda Expressions
    auto max_lambda = [](auto a, auto b) { return a > b ? a : b; };
    auto greater_lambda = [](auto a, auto b) { return a > b; };
    auto less_lambda = [](auto a, auto b) { return a < b; };
    auto minmax_lambda = [](auto begin, auto end) {
        if (begin == end) return std::make_pair(*begin, *begin);
        auto min_val = *begin;
        auto max_val = *begin;
        for (auto it = begin; it != end; ++it) {
            if (*it < min_val) min_val = *it;
            if (*it > max_val) max_val = *it;
        }
        return std::make_pair(min_val, max_val);
    };

    // Testing with integers
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};

    // Using function objects
    MaxFunctor<int> max_func;
    GreaterFunctor<int> greater_func;
    LessFunctor<int> less_func;
    MinMaxFunctor<int> minmax_func;

    // Test Max
    std::cout << "Max (Functor): " << max_func(5, 3) << std::endl;
    std::cout << "Max (Lambda): " << max_lambda(5, 3) << std::endl;

    // Test Greater
    std::cout << "Greater (Functor): " << greater_func(5, 3) << std::endl;
    std::cout << "Greater (Lambda): " << greater_lambda(5, 3) << std::endl;

    // Test Less
    std::cout << "Less (Functor): " << less_func(5, 3) << std::endl;
    std::cout << "Less (Lambda): " << less_lambda(5, 3) << std::endl;

    // Test MinMax
    auto [min_val, max_val] = minmax_func(numbers.begin(), numbers.end());
    std::cout << "MinMax (Functor): Min=" << min_val << ", Max=" << max_val << std::endl;

    auto [min_lambda, max_lambda_val] = minmax_lambda(numbers.begin(), numbers.end());
    std::cout << "MinMax (Lambda): Min=" << min_lambda << ", Max=" << max_lambda_val << std::endl;

    return 0;
} 