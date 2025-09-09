cmake_minimum_required(VERSION 3.10)

project(cgame)

set(SRC_DIR "src/")
set(RAYLIB_DIR "lib/raylib")

# Collect your source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}*.cpp")

# Add raylib as a subproject
add_subdirectory(${RAYLIB_DIR})

# Create your executable
add_executable(cgame ${SRC_FILES})

# Include your own headers
target_include_directories(cgame PRIVATE include)

# Link with raylib (Raylib will handle platform libs internally)
target_link_libraries(cgame raylib)

# Set output directory
set_target_properties(cgame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
