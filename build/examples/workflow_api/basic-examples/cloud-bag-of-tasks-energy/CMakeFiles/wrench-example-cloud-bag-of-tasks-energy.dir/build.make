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
include examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/progress.make

# Include the compile flags for this target's objects.
include examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/flags.make

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/flags.make
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o: /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/TwoTasksAtATimeCloudWMS.cpp
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/henric/Home/WRENCH/wrench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o -MF CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o.d -o CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o -c /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/TwoTasksAtATimeCloudWMS.cpp

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.i"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/TwoTasksAtATimeCloudWMS.cpp > CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.i

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.s"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/TwoTasksAtATimeCloudWMS.cpp -o CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.s

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/flags.make
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o: /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CloudBagOfTasksEnergy.cpp
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/henric/Home/WRENCH/wrench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o -MF CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o.d -o CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o -c /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CloudBagOfTasksEnergy.cpp

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.i"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CloudBagOfTasksEnergy.cpp > CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.i

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.s"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CloudBagOfTasksEnergy.cpp -o CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.s

# Object files for target wrench-example-cloud-bag-of-tasks-energy
wrench__example__cloud__bag__of__tasks__energy_OBJECTS = \
"CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o" \
"CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o"

# External object files for target wrench-example-cloud-bag-of-tasks-energy
wrench__example__cloud__bag__of__tasks__energy_EXTERNAL_OBJECTS =

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/TwoTasksAtATimeCloudWMS.cpp.o
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/CloudBagOfTasksEnergy.cpp.o
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/build.make
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy: libwrench.a
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy: /usr/local/lib/libsimgrid.dylib
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/henric/Home/WRENCH/wrench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable wrench-example-cloud-bag-of-tasks-energy"
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/build: examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/wrench-example-cloud-bag-of-tasks-energy
.PHONY : examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/build

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/clean:
	cd /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy && $(CMAKE_COMMAND) -P CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/cmake_clean.cmake
.PHONY : examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/clean

examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/depend:
	cd /Users/henric/Home/WRENCH/wrench/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/henric/Home/WRENCH/wrench /Users/henric/Home/WRENCH/wrench/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy /Users/henric/Home/WRENCH/wrench/build /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy /Users/henric/Home/WRENCH/wrench/build/examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/workflow_api/basic-examples/cloud-bag-of-tasks-energy/CMakeFiles/wrench-example-cloud-bag-of-tasks-energy.dir/depend

