# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I"C:/msys64/mingw64/include"
LDFLAGS := -LC:/msys64/mingw64/lib -lexpat



# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := testsrc

# List of source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executables
EXEC := $(BIN_DIR)/testdsv.exe

# Google Test
GTEST_LIB := -lgtest -lgtest_main -pthread

all: $(EXEC)

# Create necessary directories if they don't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR) 2>NUL || :

$(BIN_DIR):
	mkdir $(BIN_DIR) 2>NUL || :

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files into final executable
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS) $(LDLIBS)

$(BIN_DIR)/string_utils.exe: $(OBJ_DIR)/StringUtils.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Run tests
test: $(EXEC)
	$(EXEC)

# Clean rule (Windows-friendly)
clean:
	-rmdir /S /Q bin 2>NUL || :
	-rmdir /S /Q obj 2>NUL || :
	del /F /Q bin/*.exe 2>NUL || :
	del /F /Q obj/*.o 2>NUL || :


.PHONY: clean test

