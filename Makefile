# Compiler and flags
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
INCLUDES=-I./proj2/include

# Directories
SRCDIR=proj2/src
TESTDIR=proj2/testsrc
OBJDIR=obj
BINDIR=bin

# Source files
SRCFILES=proj2/src/StringDataSource.cpp proj2/src/StringDataSink.cpp
OBJFILES=$(patsubst proj2/src/%.cpp, $(OBJDIR)/%.o, $(SRCFILES))

# Compile source files
$(OBJDIR)/%.o: proj2/src/%.cpp
	@echo "Compiling source file: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile test files ONLY IF USE_GTEST IS ENABLED
ifdef USE_GTEST
TESTFILES=proj2/testsrc/StringUtilsTest.cpp proj2/testsrc/StringDataSourceTest.cpp proj2/testsrc/StringDataSinkTest.cpp
TESTOBJFILES=$(patsubst proj2/testsrc/%.cpp, $(OBJDIR)/%.o, $(TESTFILES))

$(OBJDIR)/%.o: proj2/testsrc/%.cpp
	@echo "Compiling test file: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -DUSE_GTEST -c $< -o $@
endif

# Link executable
$(BINDIR)/proj2_executable: $(OBJFILES)
	$(CXX) $^ -o $@

all: directories $(BINDIR)/proj2_executable

directories:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)

clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

.PHONY: all directories clean
