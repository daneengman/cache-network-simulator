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
CMAKE_SOURCE_DIR = /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss

# Include any dependencies generated for this target.
include simpleCache/CMakeFiles/simpleCache.dir/depend.make

# Include the progress variables for this target.
include simpleCache/CMakeFiles/simpleCache.dir/progress.make

# Include the compile flags for this target's objects.
include simpleCache/CMakeFiles/simpleCache.dir/flags.make

simpleCache/CMakeFiles/simpleCache.dir/cache.c.o: simpleCache/CMakeFiles/simpleCache.dir/flags.make
simpleCache/CMakeFiles/simpleCache.dir/cache.c.o: simpleCache/cache.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object simpleCache/CMakeFiles/simpleCache.dir/cache.c.o"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/simpleCache.dir/cache.c.o   -c /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/cache.c

simpleCache/CMakeFiles/simpleCache.dir/cache.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simpleCache.dir/cache.c.i"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/cache.c > CMakeFiles/simpleCache.dir/cache.c.i

simpleCache/CMakeFiles/simpleCache.dir/cache.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simpleCache.dir/cache.c.s"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/cache.c -o CMakeFiles/simpleCache.dir/cache.c.s

simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.requires:
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.requires

simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.provides: simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.requires
	$(MAKE) -f simpleCache/CMakeFiles/simpleCache.dir/build.make simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.provides.build
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.provides

simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.provides.build: simpleCache/CMakeFiles/simpleCache.dir/cache.c.o

simpleCache/CMakeFiles/simpleCache.dir/stree.c.o: simpleCache/CMakeFiles/simpleCache.dir/flags.make
simpleCache/CMakeFiles/simpleCache.dir/stree.c.o: simpleCache/stree.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object simpleCache/CMakeFiles/simpleCache.dir/stree.c.o"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/simpleCache.dir/stree.c.o   -c /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/stree.c

simpleCache/CMakeFiles/simpleCache.dir/stree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simpleCache.dir/stree.c.i"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/stree.c > CMakeFiles/simpleCache.dir/stree.c.i

simpleCache/CMakeFiles/simpleCache.dir/stree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simpleCache.dir/stree.c.s"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/stree.c -o CMakeFiles/simpleCache.dir/stree.c.s

simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.requires:
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.requires

simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.provides: simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.requires
	$(MAKE) -f simpleCache/CMakeFiles/simpleCache.dir/build.make simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.provides.build
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.provides

simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.provides.build: simpleCache/CMakeFiles/simpleCache.dir/stree.c.o

# Object files for target simpleCache
simpleCache_OBJECTS = \
"CMakeFiles/simpleCache.dir/cache.c.o" \
"CMakeFiles/simpleCache.dir/stree.c.o"

# External object files for target simpleCache
simpleCache_EXTERNAL_OBJECTS =

simpleCache/libsimpleCache.so: simpleCache/CMakeFiles/simpleCache.dir/cache.c.o
simpleCache/libsimpleCache.so: simpleCache/CMakeFiles/simpleCache.dir/stree.c.o
simpleCache/libsimpleCache.so: simpleCache/CMakeFiles/simpleCache.dir/build.make
simpleCache/libsimpleCache.so: simpleCache/CMakeFiles/simpleCache.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libsimpleCache.so"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpleCache.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
simpleCache/CMakeFiles/simpleCache.dir/build: simpleCache/libsimpleCache.so
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/build

simpleCache/CMakeFiles/simpleCache.dir/requires: simpleCache/CMakeFiles/simpleCache.dir/cache.c.o.requires
simpleCache/CMakeFiles/simpleCache.dir/requires: simpleCache/CMakeFiles/simpleCache.dir/stree.c.o.requires
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/requires

simpleCache/CMakeFiles/simpleCache.dir/clean:
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache && $(CMAKE_COMMAND) -P CMakeFiles/simpleCache.dir/cmake_clean.cmake
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/clean

simpleCache/CMakeFiles/simpleCache.dir/depend:
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/simpleCache/CMakeFiles/simpleCache.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : simpleCache/CMakeFiles/simpleCache.dir/depend

