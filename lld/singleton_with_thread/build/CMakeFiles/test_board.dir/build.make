# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = /Users/manoj/Documents/CPP/lld/singleton_with_thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/manoj/Documents/CPP/lld/singleton_with_thread/build

# Include any dependencies generated for this target.
include CMakeFiles/test_board.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_board.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_board.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_board.dir/flags.make

CMakeFiles/test_board.dir/codegen:
.PHONY : CMakeFiles/test_board.dir/codegen

CMakeFiles/test_board.dir/tests/test_board.cpp.o: CMakeFiles/test_board.dir/flags.make
CMakeFiles/test_board.dir/tests/test_board.cpp.o: /Users/manoj/Documents/CPP/lld/singleton_with_thread/tests/test_board.cpp
CMakeFiles/test_board.dir/tests/test_board.cpp.o: CMakeFiles/test_board.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/manoj/Documents/CPP/lld/singleton_with_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_board.dir/tests/test_board.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_board.dir/tests/test_board.cpp.o -MF CMakeFiles/test_board.dir/tests/test_board.cpp.o.d -o CMakeFiles/test_board.dir/tests/test_board.cpp.o -c /Users/manoj/Documents/CPP/lld/singleton_with_thread/tests/test_board.cpp

CMakeFiles/test_board.dir/tests/test_board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_board.dir/tests/test_board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/manoj/Documents/CPP/lld/singleton_with_thread/tests/test_board.cpp > CMakeFiles/test_board.dir/tests/test_board.cpp.i

CMakeFiles/test_board.dir/tests/test_board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_board.dir/tests/test_board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/manoj/Documents/CPP/lld/singleton_with_thread/tests/test_board.cpp -o CMakeFiles/test_board.dir/tests/test_board.cpp.s

CMakeFiles/test_board.dir/src/board.cpp.o: CMakeFiles/test_board.dir/flags.make
CMakeFiles/test_board.dir/src/board.cpp.o: /Users/manoj/Documents/CPP/lld/singleton_with_thread/src/board.cpp
CMakeFiles/test_board.dir/src/board.cpp.o: CMakeFiles/test_board.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/manoj/Documents/CPP/lld/singleton_with_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_board.dir/src/board.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_board.dir/src/board.cpp.o -MF CMakeFiles/test_board.dir/src/board.cpp.o.d -o CMakeFiles/test_board.dir/src/board.cpp.o -c /Users/manoj/Documents/CPP/lld/singleton_with_thread/src/board.cpp

CMakeFiles/test_board.dir/src/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_board.dir/src/board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/manoj/Documents/CPP/lld/singleton_with_thread/src/board.cpp > CMakeFiles/test_board.dir/src/board.cpp.i

CMakeFiles/test_board.dir/src/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_board.dir/src/board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/manoj/Documents/CPP/lld/singleton_with_thread/src/board.cpp -o CMakeFiles/test_board.dir/src/board.cpp.s

# Object files for target test_board
test_board_OBJECTS = \
"CMakeFiles/test_board.dir/tests/test_board.cpp.o" \
"CMakeFiles/test_board.dir/src/board.cpp.o"

# External object files for target test_board
test_board_EXTERNAL_OBJECTS =

test_board: CMakeFiles/test_board.dir/tests/test_board.cpp.o
test_board: CMakeFiles/test_board.dir/src/board.cpp.o
test_board: CMakeFiles/test_board.dir/build.make
test_board: /opt/homebrew/lib/libgtest.a
test_board: CMakeFiles/test_board.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/manoj/Documents/CPP/lld/singleton_with_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_board"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_board.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_board.dir/build: test_board
.PHONY : CMakeFiles/test_board.dir/build

CMakeFiles/test_board.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_board.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_board.dir/clean

CMakeFiles/test_board.dir/depend:
	cd /Users/manoj/Documents/CPP/lld/singleton_with_thread/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/manoj/Documents/CPP/lld/singleton_with_thread /Users/manoj/Documents/CPP/lld/singleton_with_thread /Users/manoj/Documents/CPP/lld/singleton_with_thread/build /Users/manoj/Documents/CPP/lld/singleton_with_thread/build /Users/manoj/Documents/CPP/lld/singleton_with_thread/build/CMakeFiles/test_board.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_board.dir/depend

