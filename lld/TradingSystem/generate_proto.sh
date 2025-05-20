#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Generate protocol buffer files
protoc --cpp_out=build \
    --proto_path=proto \
    proto/order.proto \
    proto/market_data.proto \
    proto/system.proto

# Copy generated files to include directory
cp build/order.pb.h include/
cp build/market_data.pb.h include/
cp build/system.pb.h include/
cp build/order.pb.cc src/
cp build/market_data.pb.cc src/
cp build/system.pb.cc src/ 