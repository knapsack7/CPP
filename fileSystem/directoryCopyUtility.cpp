#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>

namespace fs = std::filesystem;

// Function to copy a single file with progress display
bool copyFile(const fs::path& source, const fs::path& destination) {
    // Open source file in binary mode
    std::ifstream input(source, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Cannot open source file: " << source << std::endl;
        return false;
    }

    // Open destination file in binary mode
    std::ofstream output(destination, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Cannot create destination file: " << destination << std::endl;
        return false;
    }

    // Get file size
    const auto fileSize = fs::file_size(source);
    
    // Create buffer for copying
    constexpr size_t bufferSize = 4096;  // 4KB buffer
    std::vector<char> buffer(bufferSize);

    // Copy file in chunks
    size_t totalBytesRead = 0;
    while (totalBytesRead < fileSize) {
        // Calculate remaining bytes to read
        size_t remainingBytes = fileSize - totalBytesRead;
        size_t bytesToRead = std::min(bufferSize, remainingBytes);

        // Read chunk from source
        input.read(buffer.data(), bytesToRead);
        if (!input) {
            std::cerr << "Error: Failed to read from source file" << std::endl;
            return false;
        }

        // Write chunk to destination
        output.write(buffer.data(), bytesToRead);
        if (!output) {
            std::cerr << "Error: Failed to write to destination file" << std::endl;
            return false;
        }

        totalBytesRead += bytesToRead;

        // Calculate and display progress
        float progress = (static_cast<float>(totalBytesRead) / fileSize) * 100;
        std::cout << "\rProgress: " << std::fixed << std::setprecision(1) 
                  << progress << "% (" << totalBytesRead << "/" << fileSize << " bytes)";
        std::cout.flush();
    }
    std::cout << std::endl;  // New line after progress

    return true;
}

// Function to copy a directory recursively
bool copyDirectory(const fs::path& source, const fs::path& destination) {
    try {
        // Create destination directory if it doesn't exist
        if (!fs::exists(destination)) {
            fs::create_directories(destination);
        }

        // Iterate through the source directory
        for (const auto& entry : fs::directory_iterator(source)) {
            const auto& sourcePath = entry.path();
            auto destinationPath = destination / sourcePath.filename();

            if (entry.is_directory()) {
                // Recursively copy subdirectories
                if (!copyDirectory(sourcePath, destinationPath)) {
                    return false;
                }
            } else {
                // Copy file
                std::cout << "Copying: " << sourcePath.filename() << std::endl;
                if (!copyFile(sourcePath, destinationPath)) {
                    return false;
                }
            }
        }
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <source> <destination>" << std::endl;
    std::cout << "  source:      Source file or directory to copy" << std::endl;
    std::cout << "  destination: Destination file or directory" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    fs::path source = argv[1];
    fs::path destination = argv[2];

    // Check if source exists
    if (!fs::exists(source)) {
        std::cerr << "Error: Source path does not exist: " << source << std::endl;
        return 1;
    }

    try {
        if (fs::is_directory(source)) {
            std::cout << "Copying directory: " << source << " to " << destination << std::endl;
            if (!copyDirectory(source, destination)) {
                std::cerr << "Error: Failed to copy directory" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Copying file: " << source.filename() << std::endl;
            if (!copyFile(source, destination)) {
                std::cerr << "Error: Failed to copy file" << std::endl;
                return 1;
            }
        }
        std::cout << "Copy completed successfully" << std::endl;
        return 0;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
} 