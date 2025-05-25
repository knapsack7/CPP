cmake_minimum_required(VERSION 3.10)
project(DocumentEditor)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include third_party)

# Add source files
set(SOURCES
    src/main.cpp
    src/document.cpp
    src/document_element.cpp
    src/document_renderer.cpp
    src/document_storage.cpp
)

# Add header files
set(HEADERS
    include/document.h
    include/document_element.h
    include/document_renderer.h
    include/document_storage.h
)

# Create executable
add_executable(document_editor ${SOURCES} ${HEADERS})

# Add custom clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/document_editor
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/build
    COMMENT "Cleaning build directory..."
) 