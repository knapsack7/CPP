#!/bin/bash

set -e  # Exit on error

echo "Creating build directory..."
mkdir -p build
cd build

echo "Configuring with CMake..."
cmake ..

echo "Building the project..."
make -j4

echo "Running tests..."
ctest --output-on-failure

echo "Running connection tests..."
./tests/connection_test --gtest_color=yes

echo "Running trading cases tests..."
./tests/trading_cases_test --gtest_color=yes 