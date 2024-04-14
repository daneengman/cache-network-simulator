project(interconnectBusSV)
add_library(interconnectBusSV SHARED interconnectBusSV.c)
target_include_directories(interconnectBusSV PRIVATE ../common)
