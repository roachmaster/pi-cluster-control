add_executable(test_di
test_main.cpp
test_di.cpp
)

target_link_libraries(test_di PRIVATE di)

set_target_properties(test_di PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)