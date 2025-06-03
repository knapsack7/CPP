cmake_minimum_required(VERSION 3.10)
project(OnlineFoodOrderingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files
file(GLOB_RECURSE SOURCES 
    "*.cpp"
    "models/*.cpp"
    "managers/*.cpp"
    "strategies/*.cpp"
    "factories/*.cpp"
    "services/*.cpp"
    "utils/*.cpp"
)

# Exclude CMake compiler ID files
list(FILTER SOURCES EXCLUDE REGEX ".*CMakeCXXCompilerId\\.cpp$")

# Add all header files
file(GLOB_RECURSE HEADERS 
    "*.h"
    "models/*.h"
    "managers/*.h"
    "strategies/*.h"
    "factories/*.h"
    "services/*.h"
    "utils/*.h"
)

# Create executable
add_executable(OnlineFoodOrderingSystem ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(OnlineFoodOrderingSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 