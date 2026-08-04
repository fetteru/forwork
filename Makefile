# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = List

# Default target: build
all: $(TARGET)

# Build rule
$(TARGET): List.cpp
	$(CXX) $(CXXFLAGS) List.cpp -o $(TARGET)

# Build and run
run: $(TARGET)
	./$(TARGET).exe

# Clean up generated files (Windows compatible)
clean:
	-del /Q $(TARGET).exe 2>nul

.PHONY: all run clean
