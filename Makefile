# Compiler settings
CXX = g++                                    # We're using g++ compiler
CXXFLAGS = -std=c++17 -I./proj2/include     # Use C++17 and look for header files in include directory
LDFLAGS = -lgtest -lgtest_main -pthread      # Link with Google Test libraries

# Define our directories
BIN_DIR = bin      # Where our final programs go
OBJ_DIR = obj      # Where our .o files go
SRC_DIR = proj2/src        # Where our source code is
TEST_DIR = proj2/testsrc   # Where our test code is

# Make sure our directories exist
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(OBJ_DIR))

# Main target - this runs everything
all: teststrutils teststrdatasource teststrdatasink testdsv testxml

# Individual test program builds
# Each line below creates one test program by combining the needed .o files

# Test for string utilities
teststrutils: $(OBJ_DIR)/StringUtils.o $(OBJ_DIR)/StringUtilsTest.o
    $(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Test for string data source
teststrdatasource: $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringDataSourceTest.o
    $(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Test for string data sink
teststrdatasink: $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSinkTest.o
    $(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Test for DSV reader/writer
testdsv: $(OBJ_DIR)/CDSVReader.o $(OBJ_DIR)/CDSVWriter.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/CDSVReaderTest.o $(OBJ_DIR)/CDSVWriterTest.o
    $(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Test for XML reader/writer
testxml: $(OBJ_DIR)/CXMLReader.o $(OBJ_DIR)/CXMLWriter.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/CXMLReaderTest.o $(OBJ_DIR)/CXMLWriterTest.o
    $(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS) -lexpat

# Rules to create .o files from .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -c -o $@ $

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -c -o $@ $

# Run all the tests in the required order
test: all
    ./$(BIN_DIR)/teststrutils
    ./$(BIN_DIR)/teststrdatasource
    ./$(BIN_DIR)/teststrdatasink
    ./$(BIN_DIR)/testdsv
    ./$(BIN_DIR)/testxml

# Clean up all generated files
clean:
    rm -rf $(BIN_DIR) $(OBJ_DIR)

# Tell make these aren't actual files
.PHONY: all clean test