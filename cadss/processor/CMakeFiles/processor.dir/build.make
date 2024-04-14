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
include processor/CMakeFiles/processor.dir/depend.make

# Include the progress variables for this target.
include processor/CMakeFiles/processor.dir/progress.make

# Include the compile flags for this target's objects.
include processor/CMakeFiles/processor.dir/flags.make

processor/CMakeFiles/processor.dir/processor.c.o: processor/CMakeFiles/processor.dir/flags.make
processor/CMakeFiles/processor.dir/processor.c.o: processor/processor.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object processor/CMakeFiles/processor.dir/processor.c.o"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/processor.dir/processor.c.o   -c /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor/processor.c

processor/CMakeFiles/processor.dir/processor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/processor.dir/processor.c.i"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor/processor.c > CMakeFiles/processor.dir/processor.c.i

processor/CMakeFiles/processor.dir/processor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/processor.dir/processor.c.s"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor/processor.c -o CMakeFiles/processor.dir/processor.c.s

processor/CMakeFiles/processor.dir/processor.c.o.requires:
.PHONY : processor/CMakeFiles/processor.dir/processor.c.o.requires

processor/CMakeFiles/processor.dir/processor.c.o.provides: processor/CMakeFiles/processor.dir/processor.c.o.requires
	$(MAKE) -f processor/CMakeFiles/processor.dir/build.make processor/CMakeFiles/processor.dir/processor.c.o.provides.build
.PHONY : processor/CMakeFiles/processor.dir/processor.c.o.provides

processor/CMakeFiles/processor.dir/processor.c.o.provides.build: processor/CMakeFiles/processor.dir/processor.c.o

# Object files for target processor
processor_OBJECTS = \
"CMakeFiles/processor.dir/processor.c.o"

# External object files for target processor
processor_EXTERNAL_OBJECTS =

processor/libprocessor.so: processor/CMakeFiles/processor.dir/processor.c.o
processor/libprocessor.so: processor/CMakeFiles/processor.dir/build.make
processor/libprocessor.so: processor/CMakeFiles/processor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libprocessor.so"
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/processor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
processor/CMakeFiles/processor.dir/build: processor/libprocessor.so
.PHONY : processor/CMakeFiles/processor.dir/build

processor/CMakeFiles/processor.dir/requires: processor/CMakeFiles/processor.dir/processor.c.o.requires
.PHONY : processor/CMakeFiles/processor.dir/requires

processor/CMakeFiles/processor.dir/clean:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor && $(CMAKE_COMMAND) -P CMakeFiles/processor.dir/cmake_clean.cmake
.PHONY : processor/CMakeFiles/processor.dir/clean

processor/CMakeFiles/processor.dir/depend:
	cd /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/cadss/processor/CMakeFiles/processor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : processor/CMakeFiles/processor.dir/depend

