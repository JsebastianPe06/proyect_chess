# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TESTS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name
TARGET = main.exe

# Default rule
all: $(BUILD_DIR) $(TARGET)

# Link all objects and tests
$(TARGET): $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiles source files to objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build folder if it doesn't exist
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# Cleaning generated files (Windows-compatible)
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@if exist "$(TARGET)" del "$(TARGET)"