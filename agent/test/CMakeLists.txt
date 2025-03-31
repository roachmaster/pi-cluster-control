add_executable(test_agent
test_main.cpp
test_agent.cpp
)

target_link_libraries(test_agent PRIVATE agent)

set_target_properties(test_agent PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)