cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_library(common
src/common.cpp
)

target_include_directories(common PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(common PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)