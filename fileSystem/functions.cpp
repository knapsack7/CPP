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

void traversingDirectory(std::string_view path){

    fs::path  currPath{path};

    std::vector<fs::directory_entry> entries;
    for(const auto & dir_entry : fs::directory_iterator(currPath)){
        entries.push_back(dir_entry); // Removed as per request
    }
    std::partition(entries.begin(), entries.end(), [](const fs::directory_entry & de){
        return de.is_directory();
    });

    for(const auto & dir_entry : entries){
        std::cout <<  dir_entry.path() << std::endl;

        switch(const auto & path = dir_entry.path(); dir_entry.status().type()){

            case fs::file_type::regular:     
                std::cout << "Regular file: " << path.string() << "\t" << dir_entry.file_size() << std::endl;
                break;
            case fs::file_type::directory:
                std::cout << "Directory: " << path.string() << std::endl;
        }

    }

}


void directory_operations(std::string_view path){
    fs::path currPath{path};
    if (fs::exists(path) == false){  // check if path exists
        std::cout << "Directory does not exist" << std::endl;
        return;
    }
    currPath /= "newDir";
    if (!fs::create_directory(currPath)){
        std::cout << "Failed to create directory" << std::endl;
        //return;
    } else {
        std::cout << "Directory created" << std::endl;
    }

    // if (!fs::remove(currPath)){
    //     std::cout << "Failed to remove directory" << std::endl;
    //     return;
    // } else {
    //     std::cout << "Directory removed" << std::endl;
    // }

    try{
        std::cout << fs::current_path() << std::endl;
        std::cout << "Changing path ";
        fs::current_path(currPath);
        std::error_code ec;
        if(ec){
            std::cout << "Error: " << ec.message() << std::endl;
            return ;
        }
        std::cout << fs::current_path() << std::endl;
    }catch(const fs::filesystem_error & e){
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "Creating file in current directory" << std::endl;
    fs::path filePath{fs::current_path() / "newFile.txt"};
    std::ofstream outFile{filePath};
    outFile << "Hello World!" << std::endl;
    outFile.close();
}
void demo_perms(std::filesystem::perms p)
{
    using std::filesystem::perms;
    auto show = [=](char op, perms perm)
    {
        std::cout << (perms::none == (perm & p) ? '-' : op);
    };
    show('r', perms::owner_read);
    show('w', perms::owner_write);
    show('x', perms::owner_exec);
    show('r', perms::group_read);
    show('w', perms::group_write);
    show('x', perms::group_exec);
    show('r', perms::others_read);
    show('w', perms::others_write);
    show('x', perms::others_exec);
    std::cout << '\n';
}

void permissions(std::string_view file){
    fs::path file_to_modify{file};
    if (!fs::exists(file_to_modify)){
        std::cout << "File does not exist" << std::endl;
        return;
    }
    auto perm = fs::status(file_to_modify).permissions();
    demo_perms(perm);
    std::cout << "Changing permissions" << std::endl;
    fs::permissions(file_to_modify, fs::perms::owner_all, fs::perm_options::add);
    demo_perms(perm);
}


int main(){
    //usingPath();
    //traversingDirectory(R"(/Users/manoj/Documents/CPP/)");
    //directory_operations(R"(/Users/manoj/Documents/CPP/fileSystem/)");
    //traversingDirectory(R"(/Users/manoj/Documents/CPP/fileSystem/)");
    permissions(R"(/Users/manoj/Documents/CPP/fileSystem/file.txt)");
    return 0;
}


