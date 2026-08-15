# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Auto-find all .cpp files
SRCS = $(wildcard *.cpp)
# Corresponding .exe targets
TARGETS = $(SRCS:.cpp=.exe)

# Default: build all
all: $(TARGETS)

# Generic rule: build xxx.cpp into xxx.exe
%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean all executables
clean:
	-del /Q *.exe 2>nul

.PHONY: all clean
