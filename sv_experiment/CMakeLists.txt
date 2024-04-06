cmake_minimum_required(VERSION 2.8)
project(MyProject)

# Set up compilation rules for SystemVerilog files
add_custom_command(
    OUTPUT dpi_shared.so
    COMMAND vcs -full64 -shared -sverilog test.sv -o dpi_shared.so
    DEPENDS test.sv
)


# Add executable or library targets
add_executable(my_executable test.c)

# Link shared object file containing SystemVerilog DPI functions
# target_link_libraries(my_executable PRIVATE /afs/andrew.cmu.edu/usr13/dengman/private/15618/cache-network-simulator/sv_experiment/dpi_shared.so)

find_library(DPI_SHARED dpi_shared)
target_link_libraries(my_executable PRIVATE "${DPI_SHARED}")

# Include directories containing SystemVerilog headers
target_include_directories(my_executable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)