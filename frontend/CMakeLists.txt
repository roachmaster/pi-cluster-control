cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_executable(frontend
src/main.cpp
)

target_include_directories(frontend PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(frontend PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)