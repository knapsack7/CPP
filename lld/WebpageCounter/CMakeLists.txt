# Minimum CMake version required for this project
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(WebpageCounter)

# Set C++ standard to C++17 and make it required
# This ensures all compilers use at least C++17 features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings based on the compiler being used
# MSVC: Microsoft Visual C++ compiler
# Others: GCC/Clang compilers
if(MSVC)
    # Enable all warnings for MSVC
    add_compile_options(/W4)
else()
    # Enable all warnings, extra warnings, and pedantic warnings for GCC/Clang
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add include directories
# This makes the include directory available to all targets
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create the main executable
# This builds the main program with all its dependencies
add_executable(webpage_counter
    src/main.cpp              # Main program file
    src/WebpageCounter.cpp    # Counter implementation
    src/Logger.cpp           # Logger implementation
)

# Create the test executable
# This builds the test program with all its dependencies
add_executable(webpage_counter_test
    tests/WebpageCounterTest.cpp  # Test file
    src/WebpageCounter.cpp        # Counter implementation
    src/Logger.cpp               # Logger implementation
)

# Add threading support for Unix-like systems
# This links the pthread library for thread support
if(UNIX)
    # Link pthread library to both executables
    target_link_libraries(webpage_counter pthread)
    target_link_libraries(webpage_counter_test pthread)
endif()

# Set output directories for build artifacts
# This organizes the build output in a clean structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # Executables go here
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Libraries would go here

# Enable testing support
# This allows us to use CTest for running tests
enable_testing()

# Add the test to CTest
# This makes the test executable available to CTest
add_test(NAME webpage_counter_test COMMAND webpage_counter_test)
