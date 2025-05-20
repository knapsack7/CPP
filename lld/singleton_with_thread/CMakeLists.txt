# Minimum CMake version required to build this project
# This ensures compatibility with CMake features we use
cmake_minimum_required(VERSION 3.10)

# Project name and basic information
# This sets the project name and can include version, description, etc.
project(singleton_with_thread)

# Set C++ standard to C++11
# This ensures all compilers use the same C++ standard
# CMAKE_CXX_STANDARD_REQUIRED makes this a requirement, not just a preference
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory to compiler's include path
# This allows us to use #include "board.h" instead of #include "../include/board.h"
# ${PROJECT_SOURCE_DIR} is a CMake variable that points to the project root
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create the main executable
# This tells CMake to create an executable named 'main' from the listed source files
# The executable will be created in the build directory
add_executable(main 
    src/main.cpp
    src/board.cpp
)

# Enable testing support in CMake
# This allows us to use testing commands like add_test
enable_testing()

# Find and configure Google Test package
# REQUIRED means CMake will fail if GTest is not found
# This sets up GTest include paths and libraries
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create the test executable
# This creates a separate executable for running tests
# It includes both test files and source files needed for testing
add_executable(test_board
    tests/test_board.cpp
    src/board.cpp
)

# Link libraries to the test executable
# This connects the test executable with required external libraries:
# 1. ${GTEST_LIBRARIES} - Google Test framework libraries
# 2. pthread - POSIX threads library (needed for mutex in our singleton)
target_link_libraries(test_board ${GTEST_LIBRARIES} pthread)

# Register the test with CTest
# This makes the test executable available to run via 'ctest' command
# NAME is the test name, COMMAND is the executable to run
add_test(NAME test_board COMMAND test_board) 