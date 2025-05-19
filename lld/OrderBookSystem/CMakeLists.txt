cmake_minimum_required(VERSION 3.10)
project(OrderBookSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/Order.cpp
    src/OrderBook.cpp
    src/MarketData.cpp
    src/main.cpp
)

# Create main executable
add_executable(orderbook ${SOURCES})

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
add_executable(OrderBookTest tests/OrderBookTest.cpp ${SOURCES})
target_link_libraries(OrderBookTest gtest gtest_main) 