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
include libsponge/CMakeFiles/sponge.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libsponge/CMakeFiles/sponge.dir/compiler_depend.make

# Include the progress variables for this target.
include libsponge/CMakeFiles/sponge.dir/progress.make

# Include the compile flags for this target's objects.
include libsponge/CMakeFiles/sponge.dir/flags.make

libsponge/CMakeFiles/sponge.dir/byte_stream.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/byte_stream.cc.o: /home/runze/Programs/expProject102-953/libsponge/byte_stream.cc
libsponge/CMakeFiles/sponge.dir/byte_stream.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libsponge/CMakeFiles/sponge.dir/byte_stream.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/byte_stream.cc.o -MF CMakeFiles/sponge.dir/byte_stream.cc.o.d -o CMakeFiles/sponge.dir/byte_stream.cc.o -c /home/runze/Programs/expProject102-953/libsponge/byte_stream.cc

libsponge/CMakeFiles/sponge.dir/byte_stream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/byte_stream.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/byte_stream.cc > CMakeFiles/sponge.dir/byte_stream.cc.i

libsponge/CMakeFiles/sponge.dir/byte_stream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/byte_stream.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/byte_stream.cc -o CMakeFiles/sponge.dir/byte_stream.cc.s

libsponge/CMakeFiles/sponge.dir/util/address.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/address.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/address.cc
libsponge/CMakeFiles/sponge.dir/util/address.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/address.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/address.cc.o -MF CMakeFiles/sponge.dir/util/address.cc.o.d -o CMakeFiles/sponge.dir/util/address.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/address.cc

libsponge/CMakeFiles/sponge.dir/util/address.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/address.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/address.cc > CMakeFiles/sponge.dir/util/address.cc.i

libsponge/CMakeFiles/sponge.dir/util/address.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/address.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/address.cc -o CMakeFiles/sponge.dir/util/address.cc.s

libsponge/CMakeFiles/sponge.dir/util/buffer.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/buffer.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/buffer.cc
libsponge/CMakeFiles/sponge.dir/util/buffer.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/buffer.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/buffer.cc.o -MF CMakeFiles/sponge.dir/util/buffer.cc.o.d -o CMakeFiles/sponge.dir/util/buffer.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/buffer.cc

libsponge/CMakeFiles/sponge.dir/util/buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/buffer.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/buffer.cc > CMakeFiles/sponge.dir/util/buffer.cc.i

libsponge/CMakeFiles/sponge.dir/util/buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/buffer.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/buffer.cc -o CMakeFiles/sponge.dir/util/buffer.cc.s

libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/eventloop.cc
libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.o -MF CMakeFiles/sponge.dir/util/eventloop.cc.o.d -o CMakeFiles/sponge.dir/util/eventloop.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/eventloop.cc

libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/eventloop.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/eventloop.cc > CMakeFiles/sponge.dir/util/eventloop.cc.i

libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/eventloop.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/eventloop.cc -o CMakeFiles/sponge.dir/util/eventloop.cc.s

libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/file_descriptor.cc
libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.o -MF CMakeFiles/sponge.dir/util/file_descriptor.cc.o.d -o CMakeFiles/sponge.dir/util/file_descriptor.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/file_descriptor.cc

libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/file_descriptor.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/file_descriptor.cc > CMakeFiles/sponge.dir/util/file_descriptor.cc.i

libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/file_descriptor.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/file_descriptor.cc -o CMakeFiles/sponge.dir/util/file_descriptor.cc.s

libsponge/CMakeFiles/sponge.dir/util/parser.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/parser.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/parser.cc
libsponge/CMakeFiles/sponge.dir/util/parser.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/parser.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/parser.cc.o -MF CMakeFiles/sponge.dir/util/parser.cc.o.d -o CMakeFiles/sponge.dir/util/parser.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/parser.cc

libsponge/CMakeFiles/sponge.dir/util/parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/parser.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/parser.cc > CMakeFiles/sponge.dir/util/parser.cc.i

libsponge/CMakeFiles/sponge.dir/util/parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/parser.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/parser.cc -o CMakeFiles/sponge.dir/util/parser.cc.s

libsponge/CMakeFiles/sponge.dir/util/socket.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/socket.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/socket.cc
libsponge/CMakeFiles/sponge.dir/util/socket.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/socket.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/socket.cc.o -MF CMakeFiles/sponge.dir/util/socket.cc.o.d -o CMakeFiles/sponge.dir/util/socket.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/socket.cc

libsponge/CMakeFiles/sponge.dir/util/socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/socket.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/socket.cc > CMakeFiles/sponge.dir/util/socket.cc.i

libsponge/CMakeFiles/sponge.dir/util/socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/socket.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/socket.cc -o CMakeFiles/sponge.dir/util/socket.cc.s

libsponge/CMakeFiles/sponge.dir/util/tun.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/tun.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/tun.cc
libsponge/CMakeFiles/sponge.dir/util/tun.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/tun.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/tun.cc.o -MF CMakeFiles/sponge.dir/util/tun.cc.o.d -o CMakeFiles/sponge.dir/util/tun.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/tun.cc

libsponge/CMakeFiles/sponge.dir/util/tun.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/tun.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/tun.cc > CMakeFiles/sponge.dir/util/tun.cc.i

libsponge/CMakeFiles/sponge.dir/util/tun.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/tun.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/tun.cc -o CMakeFiles/sponge.dir/util/tun.cc.s

libsponge/CMakeFiles/sponge.dir/util/util.cc.o: libsponge/CMakeFiles/sponge.dir/flags.make
libsponge/CMakeFiles/sponge.dir/util/util.cc.o: /home/runze/Programs/expProject102-953/libsponge/util/util.cc
libsponge/CMakeFiles/sponge.dir/util/util.cc.o: libsponge/CMakeFiles/sponge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object libsponge/CMakeFiles/sponge.dir/util/util.cc.o"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libsponge/CMakeFiles/sponge.dir/util/util.cc.o -MF CMakeFiles/sponge.dir/util/util.cc.o.d -o CMakeFiles/sponge.dir/util/util.cc.o -c /home/runze/Programs/expProject102-953/libsponge/util/util.cc

libsponge/CMakeFiles/sponge.dir/util/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sponge.dir/util/util.cc.i"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runze/Programs/expProject102-953/libsponge/util/util.cc > CMakeFiles/sponge.dir/util/util.cc.i

libsponge/CMakeFiles/sponge.dir/util/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sponge.dir/util/util.cc.s"
	cd /home/runze/Programs/expProject102-953/build/libsponge && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runze/Programs/expProject102-953/libsponge/util/util.cc -o CMakeFiles/sponge.dir/util/util.cc.s

# Object files for target sponge
sponge_OBJECTS = \
"CMakeFiles/sponge.dir/byte_stream.cc.o" \
"CMakeFiles/sponge.dir/util/address.cc.o" \
"CMakeFiles/sponge.dir/util/buffer.cc.o" \
"CMakeFiles/sponge.dir/util/eventloop.cc.o" \
"CMakeFiles/sponge.dir/util/file_descriptor.cc.o" \
"CMakeFiles/sponge.dir/util/parser.cc.o" \
"CMakeFiles/sponge.dir/util/socket.cc.o" \
"CMakeFiles/sponge.dir/util/tun.cc.o" \
"CMakeFiles/sponge.dir/util/util.cc.o"

# External object files for target sponge
sponge_EXTERNAL_OBJECTS =

libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/byte_stream.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/address.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/buffer.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/eventloop.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/file_descriptor.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/parser.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/socket.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/tun.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/util/util.cc.o
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/build.make
libsponge/libsponge.a: libsponge/CMakeFiles/sponge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/runze/Programs/expProject102-953/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libsponge.a"
	cd /home/runze/Programs/expProject102-953/build/libsponge && $(CMAKE_COMMAND) -P CMakeFiles/sponge.dir/cmake_clean_target.cmake
	cd /home/runze/Programs/expProject102-953/build/libsponge && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sponge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libsponge/CMakeFiles/sponge.dir/build: libsponge/libsponge.a
.PHONY : libsponge/CMakeFiles/sponge.dir/build

libsponge/CMakeFiles/sponge.dir/clean:
	cd /home/runze/Programs/expProject102-953/build/libsponge && $(CMAKE_COMMAND) -P CMakeFiles/sponge.dir/cmake_clean.cmake
.PHONY : libsponge/CMakeFiles/sponge.dir/clean

libsponge/CMakeFiles/sponge.dir/depend:
	cd /home/runze/Programs/expProject102-953/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runze/Programs/expProject102-953 /home/runze/Programs/expProject102-953/libsponge /home/runze/Programs/expProject102-953/build /home/runze/Programs/expProject102-953/build/libsponge /home/runze/Programs/expProject102-953/build/libsponge/CMakeFiles/sponge.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : libsponge/CMakeFiles/sponge.dir/depend

