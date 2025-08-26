cmake_minimum_required(VERSION 3.10)

project(cgame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/lib/raylib" CACHE PATH "Path to Raylib directory")

# Collect source files (explicit listing preferred)
set(SRC_FILES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/Scene.cpp
    ${SRC_DIR}/Rigidbody.cpp
    ${SRC_DIR}/Entity.cpp
    # Add more .cpp files here
)

# Fail if main.cpp doesn’t exist
if(NOT EXISTS ${SRC_DIR}/Main.cpp)
    message(FATAL_ERROR "No source files found in ${SRC_DIR}")
endif()

# Add Raylib
if(EXISTS ${RAYLIB_DIR}/CMakeLists.txt)
    add_subdirectory(${RAYLIB_DIR})
else()
    message(FATAL_ERROR "Raylib directory not found or missing CMakeLists.txt")
endif()

# Create executable
add_executable(cgame ${SRC_FILES})

# Project headers
target_include_directories(cgame PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link raylib
target_link_libraries(cgame PRIVATE raylib)

# Platform-specific dependencies
if(WIN32)
    target_link_libraries(cgame PRIVATE opengl32 gdi32 winmm)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(cgame PRIVATE pthread dl m)
endif()

# Output directories
set_target_properties(cgame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)



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
