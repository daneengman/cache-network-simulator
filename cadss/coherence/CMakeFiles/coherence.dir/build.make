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
include coherence/CMakeFiles/coherence.dir/depend.make

# Include the progress variables for this target.
include coherence/CMakeFiles/coherence.dir/progress.make

# Include the compile flags for this target's objects.
include coherence/CMakeFiles/coherence.dir/flags.make

coherence/CMakeFiles/coherence.dir/coherence.c.o: coherence/CMakeFiles/coherence.dir/flags.make
coherence/CMakeFiles/coherence.dir/coherence.c.o: coherence/coherence.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object coherence/CMakeFiles/coherence.dir/coherence.c.o"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/coherence.dir/coherence.c.o   -c /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/coherence.c

coherence/CMakeFiles/coherence.dir/coherence.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/coherence.dir/coherence.c.i"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/coherence.c > CMakeFiles/coherence.dir/coherence.c.i

coherence/CMakeFiles/coherence.dir/coherence.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/coherence.dir/coherence.c.s"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/coherence.c -o CMakeFiles/coherence.dir/coherence.c.s

coherence/CMakeFiles/coherence.dir/coherence.c.o.requires:
.PHONY : coherence/CMakeFiles/coherence.dir/coherence.c.o.requires

coherence/CMakeFiles/coherence.dir/coherence.c.o.provides: coherence/CMakeFiles/coherence.dir/coherence.c.o.requires
	$(MAKE) -f coherence/CMakeFiles/coherence.dir/build.make coherence/CMakeFiles/coherence.dir/coherence.c.o.provides.build
.PHONY : coherence/CMakeFiles/coherence.dir/coherence.c.o.provides

coherence/CMakeFiles/coherence.dir/coherence.c.o.provides.build: coherence/CMakeFiles/coherence.dir/coherence.c.o

coherence/CMakeFiles/coherence.dir/protocol.c.o: coherence/CMakeFiles/coherence.dir/flags.make
coherence/CMakeFiles/coherence.dir/protocol.c.o: coherence/protocol.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object coherence/CMakeFiles/coherence.dir/protocol.c.o"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/coherence.dir/protocol.c.o   -c /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/protocol.c

coherence/CMakeFiles/coherence.dir/protocol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/coherence.dir/protocol.c.i"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/protocol.c > CMakeFiles/coherence.dir/protocol.c.i

coherence/CMakeFiles/coherence.dir/protocol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/coherence.dir/protocol.c.s"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/protocol.c -o CMakeFiles/coherence.dir/protocol.c.s

coherence/CMakeFiles/coherence.dir/protocol.c.o.requires:
.PHONY : coherence/CMakeFiles/coherence.dir/protocol.c.o.requires

coherence/CMakeFiles/coherence.dir/protocol.c.o.provides: coherence/CMakeFiles/coherence.dir/protocol.c.o.requires
	$(MAKE) -f coherence/CMakeFiles/coherence.dir/build.make coherence/CMakeFiles/coherence.dir/protocol.c.o.provides.build
.PHONY : coherence/CMakeFiles/coherence.dir/protocol.c.o.provides

coherence/CMakeFiles/coherence.dir/protocol.c.o.provides.build: coherence/CMakeFiles/coherence.dir/protocol.c.o

coherence/CMakeFiles/coherence.dir/stree.c.o: coherence/CMakeFiles/coherence.dir/flags.make
coherence/CMakeFiles/coherence.dir/stree.c.o: coherence/stree.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object coherence/CMakeFiles/coherence.dir/stree.c.o"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/coherence.dir/stree.c.o   -c /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/stree.c

coherence/CMakeFiles/coherence.dir/stree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/coherence.dir/stree.c.i"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/stree.c > CMakeFiles/coherence.dir/stree.c.i

coherence/CMakeFiles/coherence.dir/stree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/coherence.dir/stree.c.s"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/stree.c -o CMakeFiles/coherence.dir/stree.c.s

coherence/CMakeFiles/coherence.dir/stree.c.o.requires:
.PHONY : coherence/CMakeFiles/coherence.dir/stree.c.o.requires

coherence/CMakeFiles/coherence.dir/stree.c.o.provides: coherence/CMakeFiles/coherence.dir/stree.c.o.requires
	$(MAKE) -f coherence/CMakeFiles/coherence.dir/build.make coherence/CMakeFiles/coherence.dir/stree.c.o.provides.build
.PHONY : coherence/CMakeFiles/coherence.dir/stree.c.o.provides

coherence/CMakeFiles/coherence.dir/stree.c.o.provides.build: coherence/CMakeFiles/coherence.dir/stree.c.o

# Object files for target coherence
coherence_OBJECTS = \
"CMakeFiles/coherence.dir/coherence.c.o" \
"CMakeFiles/coherence.dir/protocol.c.o" \
"CMakeFiles/coherence.dir/stree.c.o"

# External object files for target coherence
coherence_EXTERNAL_OBJECTS =

coherence/libcoherence.so: coherence/CMakeFiles/coherence.dir/coherence.c.o
coherence/libcoherence.so: coherence/CMakeFiles/coherence.dir/protocol.c.o
coherence/libcoherence.so: coherence/CMakeFiles/coherence.dir/stree.c.o
coherence/libcoherence.so: coherence/CMakeFiles/coherence.dir/build.make
coherence/libcoherence.so: coherence/CMakeFiles/coherence.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libcoherence.so"
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coherence.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
coherence/CMakeFiles/coherence.dir/build: coherence/libcoherence.so
.PHONY : coherence/CMakeFiles/coherence.dir/build

coherence/CMakeFiles/coherence.dir/requires: coherence/CMakeFiles/coherence.dir/coherence.c.o.requires
coherence/CMakeFiles/coherence.dir/requires: coherence/CMakeFiles/coherence.dir/protocol.c.o.requires
coherence/CMakeFiles/coherence.dir/requires: coherence/CMakeFiles/coherence.dir/stree.c.o.requires
.PHONY : coherence/CMakeFiles/coherence.dir/requires

coherence/CMakeFiles/coherence.dir/clean:
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence && $(CMAKE_COMMAND) -P CMakeFiles/coherence.dir/cmake_clean.cmake
.PHONY : coherence/CMakeFiles/coherence.dir/clean

coherence/CMakeFiles/coherence.dir/depend:
	cd /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence /afs/ece.cmu.edu/user/dengman/private/cache-network-simulator/cadss/coherence/CMakeFiles/coherence.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : coherence/CMakeFiles/coherence.dir/depend

