# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss

# Include any dependencies generated for this target.
include branch/CMakeFiles/branch.dir/depend.make

# Include the progress variables for this target.
include branch/CMakeFiles/branch.dir/progress.make

# Include the compile flags for this target's objects.
include branch/CMakeFiles/branch.dir/flags.make

branch/CMakeFiles/branch.dir/branch.c.o: branch/CMakeFiles/branch.dir/flags.make
branch/CMakeFiles/branch.dir/branch.c.o: branch/branch.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object branch/CMakeFiles/branch.dir/branch.c.o"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/branch.dir/branch.c.o   -c /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch/branch.c

branch/CMakeFiles/branch.dir/branch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/branch.dir/branch.c.i"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch/branch.c > CMakeFiles/branch.dir/branch.c.i

branch/CMakeFiles/branch.dir/branch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/branch.dir/branch.c.s"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch/branch.c -o CMakeFiles/branch.dir/branch.c.s

branch/CMakeFiles/branch.dir/branch.c.o.requires:
.PHONY : branch/CMakeFiles/branch.dir/branch.c.o.requires

branch/CMakeFiles/branch.dir/branch.c.o.provides: branch/CMakeFiles/branch.dir/branch.c.o.requires
	$(MAKE) -f branch/CMakeFiles/branch.dir/build.make branch/CMakeFiles/branch.dir/branch.c.o.provides.build
.PHONY : branch/CMakeFiles/branch.dir/branch.c.o.provides

branch/CMakeFiles/branch.dir/branch.c.o.provides.build: branch/CMakeFiles/branch.dir/branch.c.o

# Object files for target branch
branch_OBJECTS = \
"CMakeFiles/branch.dir/branch.c.o"

# External object files for target branch
branch_EXTERNAL_OBJECTS =

branch/libbranch.so: branch/CMakeFiles/branch.dir/branch.c.o
branch/libbranch.so: branch/CMakeFiles/branch.dir/build.make
branch/libbranch.so: branch/CMakeFiles/branch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libbranch.so"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/branch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
branch/CMakeFiles/branch.dir/build: branch/libbranch.so
.PHONY : branch/CMakeFiles/branch.dir/build

branch/CMakeFiles/branch.dir/requires: branch/CMakeFiles/branch.dir/branch.c.o.requires
.PHONY : branch/CMakeFiles/branch.dir/requires

branch/CMakeFiles/branch.dir/clean:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch && $(CMAKE_COMMAND) -P CMakeFiles/branch.dir/cmake_clean.cmake
.PHONY : branch/CMakeFiles/branch.dir/clean

branch/CMakeFiles/branch.dir/depend:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/branch/CMakeFiles/branch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : branch/CMakeFiles/branch.dir/depend
