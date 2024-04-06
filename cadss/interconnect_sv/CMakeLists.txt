project(interconnect_sv)
add_library(interconnect_sv SHARED interconnect.c)
target_include_directories(interconnect_sv PRIVATE ../common)
