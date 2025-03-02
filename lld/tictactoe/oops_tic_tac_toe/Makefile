CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = tictactoe
SRC_DIR = .
OBJ_DIR = obj

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean the build
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

