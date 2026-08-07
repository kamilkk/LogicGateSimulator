# Include GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

macro(add_logic_test TEST_NAME FILE_NAME)
    add_executable(${TEST_NAME} ${FILE_NAME})
    # Link against GoogleTest and our soon-to-be-created logic_core library
    target_link_libraries(${TEST_NAME} PRIVATE gtest_main logic_core)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endmacro()

add_logic_test(test_wire test_wire.cpp)
add_logic_test(test_gate test_gate.cpp)
add_logic_test(test_simulator test_simulator.cpp)
add_logic_test(test_integration test_integration.cpp)