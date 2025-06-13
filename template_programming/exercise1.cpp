#include <utility>  // for std::pair
#include <cstddef>  // for size_t
#include <iostream>
#include <string>

// Template function to add two elements of any type
template<typename T>
T Add(const T& x, const T& y) {
    return x + y;
}

// Template function to sum array elements
template<typename T>
T ArraySum(const T* pArr, size_t arrSize) {
    T sum = T();  // Initialize with default value
    for (size_t i = 0; i < arrSize; ++i) {
        sum += pArr[i];
    }
    return sum;
}

// Template function to find maximum element in array
template<typename T>
T Max(const T* pArr, size_t arrSize) {
    if (arrSize == 0) return T();  // Return default value for empty array
    
    T maxVal = pArr[0];
    for (size_t i = 1; i < arrSize; ++i) {
        if (pArr[i] > maxVal) {
            maxVal = pArr[i];
        }
    }
    return maxVal;
}

// Template function to find minimum and maximum elements in array
template<typename T>
std::pair<T, T> MinMax(const T* pArr, size_t arrSize) {
    if (arrSize == 0) return std::make_pair(T(), T());  // Return default pair for empty array
    
    T minVal = pArr[0];
    T maxVal = pArr[0];
    
    for (size_t i = 1; i < arrSize; ++i) {
        if (pArr[i] < minVal) minVal = pArr[i];
        if (pArr[i] > maxVal) maxVal = pArr[i];
    }
    
    return std::make_pair(minVal, maxVal);
}

int main() {
    // Test with integers
    std::cout << "Testing with integers:\n";
    int a = 5, b = 3;
    std::cout << "Add(5, 3) = " << Add(a, b) << std::endl;
    
    int intArr[] = {1, 2, 3, 4, 5};
    size_t intSize = sizeof(intArr) / sizeof(intArr[0]);
    std::cout << "ArraySum = " << ArraySum(intArr, intSize) << std::endl;
    std::cout << "Max = " << Max(intArr, intSize) << std::endl;
    
    auto intMinMax = MinMax(intArr, intSize);
    std::cout << "MinMax = (" << intMinMax.first << ", " << intMinMax.second << ")\n\n";

    // Test with doubles
    std::cout << "Testing with doubles:\n";
    double x = 3.14, y = 2.86;
    std::cout << "Add(3.14, 2.86) = " << Add(x, y) << std::endl;
    
    double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    size_t doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);
    std::cout << "ArraySum = " << ArraySum(doubleArr, doubleSize) << std::endl;
    std::cout << "Max = " << Max(doubleArr, doubleSize) << std::endl;
    
    auto doubleMinMax = MinMax(doubleArr, doubleSize);
    std::cout << "MinMax = (" << doubleMinMax.first << ", " << doubleMinMax.second << ")\n\n";

    // Test with strings
    std::cout << "Testing with strings:\n";
    std::string s1 = "Hello", s2 = "World";
    std::cout << "Add(\"Hello\", \"World\") = " << Add(s1, s2) << std::endl;
    
    std::string strArr[] = {"apple", "banana", "cherry", "date"};
    size_t strSize = sizeof(strArr) / sizeof(strArr[0]);
    std::cout << "ArraySum = " << ArraySum(strArr, strSize) << std::endl;
    std::cout << "Max = " << Max(strArr, strSize) << std::endl;
    
    auto strMinMax = MinMax(strArr, strSize);
    std::cout << "MinMax = (" << strMinMax.first << ", " << strMinMax.second << ")\n\n";

    // Test with empty array
    std::cout << "Testing with empty array:\n";
    int emptyArr[] = {};
    size_t emptySize = 0;
    std::cout << "ArraySum = " << ArraySum(emptyArr, emptySize) << std::endl;
    std::cout << "Max = " << Max(emptyArr, emptySize) << std::endl;
    
    auto emptyMinMax = MinMax(emptyArr, emptySize);
    std::cout << "MinMax = (" << emptyMinMax.first << ", " << emptyMinMax.second << ")\n";

    return 0;
}
