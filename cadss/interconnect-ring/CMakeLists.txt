project(interconnect-ring)
add_library(interconnect-ring SHARED interconnect.c ring.h c_connection.h packet.h c_connection.cpp)
target_include_directories(interconnect-ring PRIVATE ../common)
