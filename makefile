CXX = g++
CXXFLAGS = -std=c++20

# Automatically detect source files
SRCS := $(wildcard *.cpp)

# Generate object file names from source files
OBJS := $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Compile the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each source file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)

# Clean .pgm files starting with 'output'
clean-pgm:
	find . -name 'output*.pgm' -exec rm {} +

# Run the main program
run: clean-pgm $(TARGET)
	./$(TARGET) $(ARGS)

.PHONY: clean run clean-pgm
