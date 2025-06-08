#include <iostream>
#include <string>
#include <algorithm>
#include <functional>


// Time Complexity: O(n + m) average case, O(nm) worst case
// where n is text length and m is pattern length
void searchWithBoyerMoore(const std::string& text, const std::string& pattern) {
    auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    auto it = std::search(text.begin(), text.end(), searcher);
    
    if (it != text.end()) {
        std::cout << "Pattern found at position: " << (it - text.begin()) << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }
}

// Time Complexity: O(n + m) average case, O(nm) worst case
// where n is text length and m is pattern length
// Generally faster than Boyer-Moore for small alphabets
void searchWithBoyerMooreHorspool(const std::string& text, const std::string& pattern) {
    auto searcher = std::boyer_moore_horspool_searcher(pattern.begin(), pattern.end());
    auto it = std::search(text.begin(), text.end(), searcher);
    
    if (it != text.end()) {
        std::cout << "Pattern found at position: " << (it - text.begin()) << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }
}

int main() {
    std::string text = "Hello World, this is a test string for pattern matching";
    std::string pattern = "pattern";

    std::cout << "Using Boyer-Moore:" << std::endl;
    searchWithBoyerMoore(text, pattern);

    std::cout << "\nUsing Boyer-Moore-Horspool:" << std::endl;
    searchWithBoyerMooreHorspool(text, pattern);

    // Compare with standard find
    std::cout << "\nUsing standard find:" << std::endl;
    size_t pos = text.find(pattern);
    if (pos != std::string::npos) {
        std::cout << "Pattern found at position: " << pos << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }

    return 0;
} 