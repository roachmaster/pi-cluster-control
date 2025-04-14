# forge-core/CMakeLists.txt

add_library(forge_core_lib
        src/forge_core.cpp
        )

target_include_directories(forge_core_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

set_target_properties(forge_core_lib PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

# Include bdd utilities
add_subdirectory(bdd)