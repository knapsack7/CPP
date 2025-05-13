#include <iostream>
#include <unistd.h>

void leak_memory() {
    int* leak = new int[10]; // Intentionally leaked memory
    (void)leak; // Suppress unused variable warning
}

int main() {
    leak_memory();
    std::cout << "Running program...\n";
    sleep(100); // Keep program alive for analysis
    return 0;
}
