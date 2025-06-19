#include <fstream>
#include <iostream>


/*
 * FILESYSTEM:
 * C++17 added support for working with filesystem components
 * Adopted from Boost.Filesystem, it was asjuted to new language
 * standards and made consistent with other parts of the library
 * Provides facilities for performing following operations:
 *     manipulation of filesystem paths
 *     create, move, rename, delete directories
 *     list contents of a given directory
 *     get information about path, file permissions, etc.
 * 
 * To create, read and write files, you still use the stream library classes
 * 
 * The facilities are provided in the <filesystem> header under std::filesystem namespace
 * namespace
 * 
 *  path - allows manipulation of paths that represent existing files or directories
 *  directory_entry - represents a path with additonal information  such as
 *  file size, file times, etc.
 *  directory_iterator - an iterator that iterates over the contents of a directory
 *  functions for working with directores
 *  and much more
 * 
 * Many functions will throw std::filesystem_error exception on failure
 */

#include <filesystem>
namespace fs = std::filesystem;
using namespace std;



void usingPath(){
    fs::path selectedPath{R"(/Users/manoj/Documents/CPP/fileSystem/file.txt)"};
    std::cout << selectedPath << std::endl;
    // reduce extra / on windows system
    std::cout << selectedPath << std::endl; // no effect on unix system

    if (selectedPath.has_root_name()){
        std::cout << "Root name: " << selectedPath.root_name() << std::endl;
    }
    if (selectedPath.has_root_directory()){
        std::cout << "Root directory: " << selectedPath.root_directory() << std::endl;
    }
    if (selectedPath.has_root_path()){
        std::cout << "Root path: " << selectedPath.root_path() << std::endl;
    }
    if (selectedPath.has_relative_path()){
        std::cout << "Relative path: " << selectedPath.relative_path() << std::endl;
    }
    if (selectedPath.has_parent_path()){    
        std::cout << "Parent path: " << selectedPath.parent_path() << std::endl;
    }
    if (selectedPath.has_filename()){
        std::cout << "Filename: " << selectedPath.filename() << std::endl;
    }
    if (selectedPath.has_stem()){
        std::cout << "Stem: " << selectedPath.stem() << std::endl;
    }
    if (selectedPath.has_extension()){
        std::cout << "Extension: " << selectedPath.extension() << std::endl;
    }
    std::cout << "File size: " << fs::file_size(selectedPath) << std::endl;
    std::cout << "File exists: " << fs::exists(selectedPath) << std::endl;
    std::cout << "File is regular: " << fs::is_regular_file(selectedPath) << std::endl;
    std::cout << "File is directory: " << fs::is_directory(selectedPath) << std::endl;
    std::cout << "File is symbolic link: " << fs::is_symlink(selectedPath) << std::endl;
    std::cout << "File is block device: " << fs::is_block_file(selectedPath) << std::endl;
}

int main(){
    //usingPath();
    return 0;
}


