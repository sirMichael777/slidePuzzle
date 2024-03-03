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

# Run the main program
run: $(TARGET)
	./$(TARGET) $(ARGS)

.PHONY: clean run
