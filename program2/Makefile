# Makefile for compiling and running 1a.cpp through 2e.cpp

# Compiler
CXX = g++

# Flags for the compiler
CXXFLAGS = -std=c++17 -g # Added -g for debugging symbols

# Targets
TARGETS = 1a 1b 2a 2b 2c 2d 2e

# Default target
all: $(TARGETS)
	@echo "Running 1a..."
	./1a
	@echo "Running 1b..."
	./1b
	@echo "Running 2a..."
	./2a 
	@echo "Running 2b..."
	./2b 
	@echo "Running 2c..."
	./2c 
	@echo "Running 2d..."
	./2d 
	@echo "Running 2e. Please follow prompts for input."
	./2e 

# Compile 1a.cpp
1a: 1a.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Compile 1b.cpp
1b: 1b.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Compile 2a.cpp
2a: 2a.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Compile 2b.cpp 
2b: 2b.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< 

# Compile 2c.cpp 
2c: 2c.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< 

# Compile 2d.cpp 
2d: 2d.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< 

# Compile 2e.cpp without ARG1 and ARG2
2e: 2e.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean target
clean:
	$(RM) $(TARGETS)
