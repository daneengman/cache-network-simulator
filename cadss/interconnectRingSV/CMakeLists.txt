project(interconnectRingSV)
add_library(interconnectRingSV SHARED interconnectRingSV.c)
target_include_directories(interconnectRingSV PRIVATE ../common)
