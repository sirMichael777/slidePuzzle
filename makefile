CXX = g++
CXXFLAGS = -std=c++20

# List of source files
SRCS = main.cpp TileManager.cpp Tile.cpp PGMImageProcessor.cpp

# List of object files
OBJS = $(SRCS:.cpp=.o)

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
