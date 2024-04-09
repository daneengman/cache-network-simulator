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
include interconnect/CMakeFiles/interconnect.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include interconnect/CMakeFiles/interconnect.dir/compiler_depend.make

# Include the progress variables for this target.
include interconnect/CMakeFiles/interconnect.dir/progress.make

# Include the compile flags for this target's objects.
include interconnect/CMakeFiles/interconnect.dir/flags.make

interconnect/CMakeFiles/interconnect.dir/interconnect.c.o: interconnect/CMakeFiles/interconnect.dir/flags.make
interconnect/CMakeFiles/interconnect.dir/interconnect.c.o: interconnect/interconnect.c
interconnect/CMakeFiles/interconnect.dir/interconnect.c.o: interconnect/CMakeFiles/interconnect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object interconnect/CMakeFiles/interconnect.dir/interconnect.c.o"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT interconnect/CMakeFiles/interconnect.dir/interconnect.c.o -MF CMakeFiles/interconnect.dir/interconnect.c.o.d -o CMakeFiles/interconnect.dir/interconnect.c.o -c /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect/interconnect.c

interconnect/CMakeFiles/interconnect.dir/interconnect.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interconnect.dir/interconnect.c.i"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect/interconnect.c > CMakeFiles/interconnect.dir/interconnect.c.i

interconnect/CMakeFiles/interconnect.dir/interconnect.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interconnect.dir/interconnect.c.s"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect/interconnect.c -o CMakeFiles/interconnect.dir/interconnect.c.s

# Object files for target interconnect
interconnect_OBJECTS = \
"CMakeFiles/interconnect.dir/interconnect.c.o"

# External object files for target interconnect
interconnect_EXTERNAL_OBJECTS =

interconnect/libinterconnect.so: interconnect/CMakeFiles/interconnect.dir/interconnect.c.o
interconnect/libinterconnect.so: interconnect/CMakeFiles/interconnect.dir/build.make
interconnect/libinterconnect.so: interconnect/CMakeFiles/interconnect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libinterconnect.so"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interconnect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
interconnect/CMakeFiles/interconnect.dir/build: interconnect/libinterconnect.so
.PHONY : interconnect/CMakeFiles/interconnect.dir/build

interconnect/CMakeFiles/interconnect.dir/clean:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect && $(CMAKE_COMMAND) -P CMakeFiles/interconnect.dir/cmake_clean.cmake
.PHONY : interconnect/CMakeFiles/interconnect.dir/clean

interconnect/CMakeFiles/interconnect.dir/depend:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/interconnect/CMakeFiles/interconnect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interconnect/CMakeFiles/interconnect.dir/depend
