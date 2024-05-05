cmake_minimum_required(VERSION 2.8) # ECE machine does not have version 3

set(CMAKE_C_COMPILER gcc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# For debugging.
set(CMAKE_C_FLAGS "-O0 -ggdb3 -DDEBUG -std=gnu99")
set(CMAKE_CXX_FLAGS "-O0 -DDEBUG -std=c++11")

# set(CMAKE_C_FLAGS "-O2 -ggdb -DDEBUG -std=gnu99")

add_subdirectory(branch)
add_subdirectory(cache)
add_subdirectory(engine)
add_subdirectory(trace)
add_subdirectory(processor)
add_subdirectory(coherence)
add_subdirectory(interconnect)
add_subdirectory(interconnectBusSV)
add_subdirectory(interconnectRingSV)
add_subdirectory(simpleCache)
add_subdirectory(memory)

project(cadss C)
