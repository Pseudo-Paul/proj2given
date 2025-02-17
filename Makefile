# Compiler and flags
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
INCLUDES=-I./include
LDFLAGS=-lgtest -lgtest_main -pthread -lexpat

# Directories
SRCDIR=src
TESTDIR=testsrc
OBJDIR=obj
BINDIR=bin

# Test executables
TESTS=$(BINDIR)/teststrutils $(BINDIR)/teststrdatasource $(BINDIR)/teststrdatasink $(BINDIR)/testdsv $(BINDIR)/testxml

# Make sure directories exist
all: directories $(TESTS)

directories:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)


# Build object files for source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build object files for test files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link test executables
$(BINDIR)/teststrutils: $(OBJDIR)/StringUtilsTest.o $(OBJDIR)/StringUtils.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/teststrdatasource: $(OBJDIR)/StringDataSourceTest.o $(OBJDIR)/StringDataSource.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/teststrdatasink: $(OBJDIR)/StringDataSinkTest.o $(OBJDIR)/StringDataSink.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/testdsv: $(OBJDIR)/DSVTest.o $(OBJDIR)/CDSVReader.o $(OBJDIR)/CDSVWriter.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/testxml: $(OBJDIR)/XMLTest.o $(OBJDIR)/CXMLReader.o $(OBJDIR)/CXMLWriter.o
	$(CXX) $^ $(LDFLAGS) -o $@

# Clean the target
clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)


.PHONY: all directories clean
