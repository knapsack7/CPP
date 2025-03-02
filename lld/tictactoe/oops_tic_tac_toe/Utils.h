#pragma once

#include <memory>
#include <utility>

namespace std {
    // Implementation of make_unique for C++11
    // This provides functionality similar to the C++14 std::make_unique
    template<typename T, typename... Args>
    typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // Specialization for array types with unknown bound
    template<typename T>
    typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
    make_unique(size_t size) {
        typedef typename std::remove_extent<T>::type U;
        return std::unique_ptr<T>(new U[size]());
    }

    // Specialization for array types with known bound (deleted)
    template<typename T, typename... Args>
    typename std::enable_if<std::is_array<T>::value && std::extent<T>::value != 0, std::unique_ptr<T>>::type
    make_unique(Args&&...) = delete;
}

