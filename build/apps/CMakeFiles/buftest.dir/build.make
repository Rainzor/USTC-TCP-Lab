# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runze/Programs/expProject102-953

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runze/Programs/expProject102-953/build

# Include any dependencies generated for this target.
include apps/CMakeFiles/buftest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include apps/CMakeFiles/buftest.dir/compiler_depend.make

# Include the progress variables for this target.
include apps/CMakeFiles/buftest.dir/progress.make

# Include the compile flags for this target's objects.
include apps/CMakeFiles/buftest.dir/flags.make

apps/CMakeFiles/buftest.dir/buftest.cc.o: apps/CMakeFiles/buftest.dir/flags.make
apps/CMakeFiles/buftest.dir/buftest.cc.o: /home/runze/Programs/expProject102-953/apps/buftest.cc
apps/CMakeFiles/buftest.dir/buftest.cc.o: apps/CMakeFiles/buftest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/CMakeFiles/buftest.dir/buftest.cc.o"
	cd /home/runze/Programs/expProject102-953/build/apps && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/CMakeFiles/buftest.dir/buftest.cc.o -MF CMakeFiles/buftest.dir/buftest.cc.o.d -o CMakeFiles/buftest.dir/buftest.cc.o -c /home/runze/Programs/expProject102-953/apps/buftest.cc

apps/CMakeFiles/buftest.dir/buftest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/buftest.dir/buftest.cc.i"
	cd /home/runze/Programs/expProject102-953/build/apps && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/apps/buftest.cc > CMakeFiles/buftest.dir/buftest.cc.i

apps/CMakeFiles/buftest.dir/buftest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/buftest.dir/buftest.cc.s"
	cd /home/runze/Programs/expProject102-953/build/apps && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/apps/buftest.cc -o CMakeFiles/buftest.dir/buftest.cc.s

# Object files for target buftest
buftest_OBJECTS = \
"CMakeFiles/buftest.dir/buftest.cc.o"

# External object files for target buftest
buftest_EXTERNAL_OBJECTS =

apps/buftest: apps/CMakeFiles/buftest.dir/buftest.cc.o
apps/buftest: apps/CMakeFiles/buftest.dir/build.make
apps/buftest: libsponge/libsponge.a
apps/buftest: /usr/lib/x86_64-linux-gnu/libpthread.a
apps/buftest: apps/CMakeFiles/buftest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable buftest"
	cd /home/runze/Programs/expProject102-953/build/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/buftest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/CMakeFiles/buftest.dir/build: apps/buftest
.PHONY : apps/CMakeFiles/buftest.dir/build

apps/CMakeFiles/buftest.dir/clean:
	cd /home/runze/Programs/expProject102-953/build/apps && $(CMAKE_COMMAND) -P CMakeFiles/buftest.dir/cmake_clean.cmake
.PHONY : apps/CMakeFiles/buftest.dir/clean

apps/CMakeFiles/buftest.dir/depend:
	cd /home/runze/Programs/expProject102-953/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runze/Programs/expProject102-953 /home/runze/Programs/expProject102-953/apps /home/runze/Programs/expProject102-953/build /home/runze/Programs/expProject102-953/build/apps /home/runze/Programs/expProject102-953/build/apps/CMakeFiles/buftest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : apps/CMakeFiles/buftest.dir/depend

