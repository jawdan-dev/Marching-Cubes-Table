cmake_minimum_required(VERSION 3.11)
project(MarchingCubesTable)

# Executable Declaration.
add_executable(MarchingCubesTable ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
target_sources(MarchingCubesTable PRIVATE ${SRC_FILES})

# Set output directory.
set(TARGET_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)

# Target Properties.
set_target_properties(
    MarchingCubesTable
    PROPERTIES
    CXX_STANDARD 20
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_OUTPUT_DIRECTORY}
)

# Includes.
target_include_directories(
    MarchingCubesTable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/
)