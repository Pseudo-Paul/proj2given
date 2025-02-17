CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
INCLUDES=-I./INCLUDES
LDFLAGS=-lgtest -lgtest_main -pthread -lexpat

# Directory variables
SRCDIR=src
OBJDIR=obj
BINDIR=bin

all: directories $(BINDIR)/teststrutils

# Create necessary directories
directories:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

# Compile cpp files from src
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile cpp files from testsrc
$(OBJDIR)/%.o: testsrc/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link test executable
$(BINDIR)/teststrutils: $(OBJDIR)/StringUtilsTest.o $(OBJDIR)/StringUtils.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all directories clean