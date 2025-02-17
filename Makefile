# Compiler and flags
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
INCLUDES=-I./proj2/include
LDFLAGS=-lgtest -lgtest_main -pthread -lexpat

# Directories
SRCDIR=proj2/src
TESTDIR=proj2/testsrc
OBJDIR=obj
BINDIR=bin

# Test executables
TESTS=$(BINDIR)/teststrutils $(BINDIR)/teststrdatasource $(BINDIR)/teststrdatasink

# Ensure directories exist
all: directories $(TESTS)

directories:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)

# Build object files for source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build object files for test files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@echo "Compiling test: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link test executables
$(BINDIR)/teststrutils: $(OBJDIR)/StringUtilsTest.o $(OBJDIR)/StringUtils.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/teststrdatasource: $(OBJDIR)/StringDataSourceTest.o $(OBJDIR)/StringDataSource.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(BINDIR)/teststrdatasink: $(OBJDIR)/StringDataSinkTest.o $(OBJDIR)/StringDataSink.o
	$(CXX) $^ $(LDFLAGS) -o $@

# Clean target
clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

.PHONY: all directories clean
