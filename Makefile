CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
INCLUDES=-I./include
LDFLAGS=-lgtest -lgtest_main -pthread -lexpat

# Directory variables
SRCDIR=src
OBJDIR=obj
BINDIR=bin

# Find all cpp files in src and testsrc
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
TESTSOURCES=$(wildcard testsrc/*.cpp)

# Generate object files in obj directory
OBJECTS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TESTOBJECTS=$(TESTSOURCES:testsrc/%.cpp=$(OBJDIR)/%.o)

# Generate test executable names
TESTBINS=\
	$(BINDIR)/teststrutils \
	$(BINDIR)/teststrdatasource \
	$(BINDIR)/teststrdatasink \
	$(BINDIR)/testdsv \
	$(BINDIR)/testxml

all: directories $(TESTBINS)

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

# Link test executables
$(BINDIR)/teststrutils: $(OBJDIR)/StringUtilsTest.o $(OBJDIR)/StringUtils.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/teststrdatasource: $(OBJDIR)/StringDataSourceTest.o $(OBJDIR)/StringDataSource.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/teststrdatasink: $(OBJDIR)/StringDataSinkTest.o $(OBJDIR)/StringDataSink.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/testdsv: $(OBJDIR)/DSVTest.o $(OBJDIR)/DSVReader.o $(OBJDIR)/DSVWriter.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/testxml: $(OBJDIR)/XMLTest.o $(OBJDIR)/XMLReader.o $(OBJDIR)/XMLWriter.o
	$(CXX) $^ $(LDFLAGS) -o $@

test: all
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all directories clean test