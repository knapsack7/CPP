cmake_minimum_required(VERSION 3.10)
project(MarketDataProcessor VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable threading
find_package(Threads REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/MarketData.cpp
    src/Processor.cpp
    src/ThreadPool.cpp
    src/Queue.cpp
    src/main.cpp
)

# Create main executable
add_executable(market_data_processor ${SOURCES})
target_link_libraries(market_data_processor PRIVATE Threads::Threads)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Add test executable
list(REMOVE_ITEM SOURCES src/main.cpp)
add_executable(MarketDataProcessorTest tests/MarketDataProcessorTest.cpp ${SOURCES})
target_link_libraries(MarketDataProcessorTest PRIVATE gtest gtest_main Threads::Threads) 