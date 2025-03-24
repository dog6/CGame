cmake_minimum_required(VERSION 3.10)

project(cgame)

# Set source directory
set(SRC_DIR "src/")
set(RAYLIB_DIR "lib/raylib")

# Include directories
include_directories(include)  # Local header files
include_directories(${RAYLIB_DIR}/src)  # Raylib source directory headers
include_directories(${RAYLIB_DIR}/external/glfw/include)  # GLFW headers

# Manually include only the needed Raylib files
set(RAYLIB_SOURCES
    ${RAYLIB_DIR}/src/core.c
    ${RAYLIB_DIR}/src/rcore_desktop_glfw.c  # or platform specific file based on your platform
    # Add more source files that you actually need here
)

# Set source files for your project
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}*.cpp")

# Create executable
add_executable(cgame ${SRC_FILES} ${RAYLIB_SOURCES})

# Find and link raylib
# Ensure the raylib directory exists and contains the necessary files
if(EXISTS ${RAYLIB_DIR}/CMakeLists.txt)
    add_subdirectory(${RAYLIB_DIR})
else()
    message(FATAL_ERROR "Raylib directory not found or missing CMakeLists.txt")
endif()
target_link_libraries(cgame raylib)

# Link other dependencies
target_link_libraries(cgame opengl32 gdi32 winmm)

# Set output directory
set_target_properties(cgame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Optionally link additional libraries like pthread and GLFW if needed
if (UNIX)
    target_link_libraries(cgame pthread)
endif()
