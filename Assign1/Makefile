CXX=g++
CXXFLAGS=-std=c++17 -Wall
TARGET=Program1
SRC=Porgram1.cpp
OBJ=$(SRC:.cpp=.o)

# The first target is the default when running 'make'
all: $(TARGET)

# Rule for linking the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule for compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for cleaning up the build
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets for commands that don't produce files with matching names
.PHONY: all clean
