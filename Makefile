# Compiler and flags
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
INCLUDES=-I./proj2/include

# Directories
SRCDIR=proj2/src
OBJDIR=obj
BINDIR=bin

# Ensure directories exist before compilation
all: directories $(BINDIR)/proj2_executable

directories:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@echo "Compiling source file: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link executable
$(BINDIR)/proj2_executable: $(OBJDIR)/StringDataSource.o $(OBJDIR)/StringDataSink.o
	$(CXX) $^ -o $@

clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

.PHONY: all directories clean
