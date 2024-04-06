project(interconnect-ring)
add_library(interconnect-ring SHARED interconnect.c)
target_include_directories(interconnect-ring PRIVATE ../common)
