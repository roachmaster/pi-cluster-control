cmake_minimum_required(VERSION 3.21)
project(forge_core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Forge Core Library ===
add_library(forge_core_lib
        # Stub source for now; you can add more as needed
        src/forge_core.cpp
        )

# Include public headers from the include/cppforge hierarchy
target_include_directories(forge_core_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

# Optional: if you have headers-only files in src/, also include:
# target_include_directories(forge_core_lib PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

# Output the binary (if any) to a consistent bin directory
set_target_properties(forge_core_lib PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

# Optional: group source files by folder in IDEs like CLion or Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/forge_manager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/forge_registry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/forge_resolver.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/forge.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/i_forge.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/cppforge_ptr.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/forgeable.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/no_op_deleter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppforge/core/forge/forge_identifiers.hpp
        )