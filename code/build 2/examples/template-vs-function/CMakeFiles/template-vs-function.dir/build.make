# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/manoj/Documents/c++/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/manoj/Documents/c++/code/build

# Include any dependencies generated for this target.
include examples/template-vs-function/CMakeFiles/template-vs-function.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/template-vs-function/CMakeFiles/template-vs-function.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/template-vs-function/CMakeFiles/template-vs-function.dir/progress.make

# Include the compile flags for this target's objects.
include examples/template-vs-function/CMakeFiles/template-vs-function.dir/flags.make

examples/template-vs-function/CMakeFiles/template-vs-function.dir/codegen:
.PHONY : examples/template-vs-function/CMakeFiles/template-vs-function.dir/codegen

examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o: examples/template-vs-function/CMakeFiles/template-vs-function.dir/flags.make
examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o: /Users/manoj/Documents/c++/code/examples/template-vs-function/template-vs-function.cpp
examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o: examples/template-vs-function/CMakeFiles/template-vs-function.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/manoj/Documents/c++/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o"
	cd /Users/manoj/Documents/c++/code/build/examples/template-vs-function && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o -MF CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o.d -o CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o -c /Users/manoj/Documents/c++/code/examples/template-vs-function/template-vs-function.cpp

examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/template-vs-function.dir/template-vs-function.cpp.i"
	cd /Users/manoj/Documents/c++/code/build/examples/template-vs-function && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/manoj/Documents/c++/code/examples/template-vs-function/template-vs-function.cpp > CMakeFiles/template-vs-function.dir/template-vs-function.cpp.i

examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/template-vs-function.dir/template-vs-function.cpp.s"
	cd /Users/manoj/Documents/c++/code/build/examples/template-vs-function && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/manoj/Documents/c++/code/examples/template-vs-function/template-vs-function.cpp -o CMakeFiles/template-vs-function.dir/template-vs-function.cpp.s

# Object files for target template-vs-function
template__vs__function_OBJECTS = \
"CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o"

# External object files for target template-vs-function
template__vs__function_EXTERNAL_OBJECTS =

examples/template-vs-function/template-vs-function: examples/template-vs-function/CMakeFiles/template-vs-function.dir/template-vs-function.cpp.o
examples/template-vs-function/template-vs-function: examples/template-vs-function/CMakeFiles/template-vs-function.dir/build.make
examples/template-vs-function/template-vs-function: examples/template-vs-function/CMakeFiles/template-vs-function.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/manoj/Documents/c++/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable template-vs-function"
	cd /Users/manoj/Documents/c++/code/build/examples/template-vs-function && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/template-vs-function.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/template-vs-function/CMakeFiles/template-vs-function.dir/build: examples/template-vs-function/template-vs-function
.PHONY : examples/template-vs-function/CMakeFiles/template-vs-function.dir/build

examples/template-vs-function/CMakeFiles/template-vs-function.dir/clean:
	cd /Users/manoj/Documents/c++/code/build/examples/template-vs-function && $(CMAKE_COMMAND) -P CMakeFiles/template-vs-function.dir/cmake_clean.cmake
.PHONY : examples/template-vs-function/CMakeFiles/template-vs-function.dir/clean

examples/template-vs-function/CMakeFiles/template-vs-function.dir/depend:
	cd /Users/manoj/Documents/c++/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/manoj/Documents/c++/code /Users/manoj/Documents/c++/code/examples/template-vs-function /Users/manoj/Documents/c++/code/build /Users/manoj/Documents/c++/code/build/examples/template-vs-function /Users/manoj/Documents/c++/code/build/examples/template-vs-function/CMakeFiles/template-vs-function.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : examples/template-vs-function/CMakeFiles/template-vs-function.dir/depend

