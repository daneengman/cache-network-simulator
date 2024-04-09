# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss

# Include any dependencies generated for this target.
include interconnect-ring/CMakeFiles/interconnect-ring.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include interconnect-ring/CMakeFiles/interconnect-ring.dir/compiler_depend.make

# Include the progress variables for this target.
include interconnect-ring/CMakeFiles/interconnect-ring.dir/progress.make

# Include the compile flags for this target's objects.
include interconnect-ring/CMakeFiles/interconnect-ring.dir/flags.make

interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.o: interconnect-ring/CMakeFiles/interconnect-ring.dir/flags.make
interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.o: interconnect-ring/interconnect.c
interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.o: interconnect-ring/CMakeFiles/interconnect-ring.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.o"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.o -MF CMakeFiles/interconnect-ring.dir/interconnect.c.o.d -o CMakeFiles/interconnect-ring.dir/interconnect.c.o -c /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring/interconnect.c

interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interconnect-ring.dir/interconnect.c.i"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring/interconnect.c > CMakeFiles/interconnect-ring.dir/interconnect.c.i

interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interconnect-ring.dir/interconnect.c.s"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring/interconnect.c -o CMakeFiles/interconnect-ring.dir/interconnect.c.s

# Object files for target interconnect-ring
interconnect__ring_OBJECTS = \
"CMakeFiles/interconnect-ring.dir/interconnect.c.o"

# External object files for target interconnect-ring
interconnect__ring_EXTERNAL_OBJECTS =

interconnect-ring/libinterconnect-ring.so: interconnect-ring/CMakeFiles/interconnect-ring.dir/interconnect.c.o
interconnect-ring/libinterconnect-ring.so: interconnect-ring/CMakeFiles/interconnect-ring.dir/build.make
interconnect-ring/libinterconnect-ring.so: interconnect-ring/CMakeFiles/interconnect-ring.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libinterconnect-ring.so"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interconnect-ring.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
interconnect-ring/CMakeFiles/interconnect-ring.dir/build: interconnect-ring/libinterconnect-ring.so
.PHONY : interconnect-ring/CMakeFiles/interconnect-ring.dir/build

interconnect-ring/CMakeFiles/interconnect-ring.dir/clean:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring && $(CMAKE_COMMAND) -P CMakeFiles/interconnect-ring.dir/cmake_clean.cmake
.PHONY : interconnect-ring/CMakeFiles/interconnect-ring.dir/clean

interconnect-ring/CMakeFiles/interconnect-ring.dir/depend:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect-ring/CMakeFiles/interconnect-ring.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interconnect-ring/CMakeFiles/interconnect-ring.dir/depend
