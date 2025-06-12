#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

bool copyFile(const fs::path& source, const fs::path& destination) {
    // Check if source exists
    if (!fs::exists(source)) {
        std::cerr << "Error: Source file does not exist" << std::endl;
        return false;
    }

    // Check if source is a directory
    if (fs::is_directory(source)) {
        std::cerr << "Error: Source is a directory" << std::endl;
        return false;
    }

    // Check if destination already exists
    if (fs::exists(destination)) {
        std::cerr << "Error: Destination file already exists" << std::endl;
        return false;
    }

    // Open source file in binary mode
    std::ifstream input(source, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Cannot open source file" << std::endl;
        return false;
    }

    // Open destination file in binary mode
    std::ofstream output(destination, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Cannot create destination file" << std::endl;
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
    }

    // Verify all bytes were copied
    if (totalBytesRead != fileSize) {
        std::cerr << "Error: File size mismatch after copy" << std::endl;
        return false;
    }

    return true;
}

int main() {
    fs::path source = fs::current_path() / "source.bin";
    fs::path destination = fs::current_path() / "copy.bin";

    if (copyFile(source, destination)) {
        std::cout << "File copied successfully" << std::endl;
        return 0;
    } else {
        std::cerr << "File copy failed" << std::endl;
        return 1;
    }
}