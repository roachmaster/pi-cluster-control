cmake_minimum_required(VERSION 3.21)
project(pi_cluster_control)

add_library(di
src/di.cpp
)

target_include_directories(di PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(di PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)