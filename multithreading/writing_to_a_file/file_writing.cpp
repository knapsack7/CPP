#include <fstream>
#include <iostream>

int main() {
    std::ofstream outFile("example.txt"); // Open file for writing (default mode: truncate)
    
    if (!outFile) { // Check if the file was successfully opened
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    outFile << "Hello, World!" << std::endl; // Write to the file
    outFile << "This is a second line." << std::endl;

    outFile.close(); // Close the file
    std::cout << "Data written to file successfully!" << std::endl;
    return 0;
}
