cmake_minimum_required(VERSION 3.21)
project(cppforge)

# 📦 Create the cppforge library
add_library(cppforge
        src/cli_logic.cpp
        src/template_renderer.cpp
)

target_include_directories(cppforge PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 🚀 Create the cppforge CLI executable
add_executable(cppforge_cli
        src/main.cpp
)

target_link_libraries(cppforge_cli PRIVATE cppforge)

set_target_properties(cppforge_cli PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
