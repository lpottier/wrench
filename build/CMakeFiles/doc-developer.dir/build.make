# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/henric/Home/WRENCH/wrench

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/henric/Home/WRENCH/wrench/build

# Utility rule file for doc-developer.

# Include any custom commands dependencies for this target.
include CMakeFiles/doc-developer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/doc-developer.dir/progress.make

doc-developer: CMakeFiles/doc-developer.dir/build.make
	mkdir -p /Users/henric/Home/WRENCH/wrench/docs/2.2-dev/developer
	/opt/local/bin/doxygen /Users/henric/Home/WRENCH/wrench/docs/logs/Doxyfile_DEVELOPER
.PHONY : doc-developer

# Rule to build all files generated by this target.
CMakeFiles/doc-developer.dir/build: doc-developer
.PHONY : CMakeFiles/doc-developer.dir/build

CMakeFiles/doc-developer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doc-developer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doc-developer.dir/clean

CMakeFiles/doc-developer.dir/depend:
	cd /Users/henric/Home/WRENCH/wrench/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/henric/Home/WRENCH/wrench /Users/henric/Home/WRENCH/wrench /Users/henric/Home/WRENCH/wrench/build /Users/henric/Home/WRENCH/wrench/build /Users/henric/Home/WRENCH/wrench/build/CMakeFiles/doc-developer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/doc-developer.dir/depend

