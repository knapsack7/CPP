cmake_minimum_required(VERSION 3.10)
project(TradingSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set paths for dependencies
set(CMAKE_PREFIX_PATH 
    ${CMAKE_PREFIX_PATH} 
    /opt/homebrew
    /opt/homebrew/opt/protobuf
)

# Find required packages
find_package(GTest REQUIRED)
find_package(Protobuf 5.29.3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(absl REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
    ${Protobuf_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${absl_INCLUDE_DIRS}
)

# Add source files (exclude main.cpp for the library)
file(GLOB_RECURSE LIB_SOURCES
    "src/*.cpp"
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Add generated protobuf sources
file(GLOB PROTO_SRCS "src/*.pb.cc")
list(APPEND LIB_SOURCES ${PROTO_SRCS})

# Add library target for core code
add_library(trading_system_lib STATIC ${LIB_SOURCES})

# Add executable (main.cpp only)
add_executable(trading_system src/main.cpp)
target_link_libraries(trading_system 
    trading_system_lib 
    protobuf::libprotobuf
    ${Boost_LIBRARIES} 
    absl::base 
    absl::synchronization 
    absl::strings 
    absl::status 
    absl::statusor 
    absl::log 
    absl::log_internal_check_op 
    absl::log_internal_conditions 
    absl::log_internal_format 
    absl::log_internal_globals 
    absl::log_internal_log_sink_set 
    absl::log_internal_message 
    absl::log_internal_nullguard 
    absl::log_internal_proto 
    absl::log_severity 
    absl::log_sink 
    pthread
)

# Add tests subdirectory
add_subdirectory(tests) 