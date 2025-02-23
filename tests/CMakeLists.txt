cmake_minimum_required(VERSION 3.14)

# Define unit test executable
add_executable(tests
    test_cpu.cpp
    test_memory.cpp
)

# Link GoogleTest libraries
target_link_libraries(tests PRIVATE gtest gtest_main)

# Add the test executable to CTest
add_test(NAME GameBoyTests COMMAND tests)
