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

# Include any dependencies generated for this target.
include examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/progress.make

# Include the compile flags for this target's objects.
include examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/flags.make

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/flags.make
examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o: /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomActionController.cpp
examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/henric/Home/WRENCH/wrench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o -MF CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o.d -o CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o -c /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomActionController.cpp

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.i"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomActionController.cpp > CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.i

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.s"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomActionController.cpp -o CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.s

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/flags.make
examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o: /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomAction.cpp
examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/henric/Home/WRENCH/wrench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o -MF CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o.d -o CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o -c /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomAction.cpp

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.i"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomAction.cpp > CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.i

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.s"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action/SuperCustomAction.cpp -o CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.s

# Object files for target wrench-example-super-custom-action
wrench__example__super__custom__action_OBJECTS = \
"CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o" \
"CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o"

# External object files for target wrench-example-super-custom-action
wrench__example__super__custom__action_EXTERNAL_OBJECTS =

examples/action_api/super-custom-action/wrench-example-super-custom-action: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomActionController.cpp.o
examples/action_api/super-custom-action/wrench-example-super-custom-action: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/SuperCustomAction.cpp.o
examples/action_api/super-custom-action/wrench-example-super-custom-action: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/build.make
examples/action_api/super-custom-action/wrench-example-super-custom-action: libwrench.a
examples/action_api/super-custom-action/wrench-example-super-custom-action: /usr/local/lib/libsimgrid.dylib
examples/action_api/super-custom-action/wrench-example-super-custom-action: examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/henric/Home/WRENCH/wrench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable wrench-example-super-custom-action"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wrench-example-super-custom-action.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/build: examples/action_api/super-custom-action/wrench-example-super-custom-action
.PHONY : examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/build

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/clean:
	cd /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action && $(CMAKE_COMMAND) -P CMakeFiles/wrench-example-super-custom-action.dir/cmake_clean.cmake
.PHONY : examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/clean

examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/depend:
	cd /Users/henric/Home/WRENCH/wrench/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/henric/Home/WRENCH/wrench /Users/henric/Home/WRENCH/wrench/examples/action_api/super-custom-action /Users/henric/Home/WRENCH/wrench/build /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action /Users/henric/Home/WRENCH/wrench/build/examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/action_api/super-custom-action/CMakeFiles/wrench-example-super-custom-action.dir/depend

