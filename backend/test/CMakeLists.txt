add_executable(test_backend
test_main.cpp
test_backend.cpp
)

target_link_libraries(test_backend PRIVATE backend)

set_target_properties(test_backend PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)