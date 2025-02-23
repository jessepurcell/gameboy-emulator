cmake_minimum_required(VERSION 3.16)
project(GameboyEmulator)

# Enable C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your emulator executable
add_executable(emulator src/main.cpp src/cpu.cpp)  # Ensure all source files are included

# Include directories (if needed)
target_include_directories(emulator PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Enable testing
enable_testing()

# Add Google Test
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/third_party/googletest")
add_subdirectory(${GTEST_DIR})

# Add test executable
add_executable(tests tests/test_cpu.cpp src/cpu.cpp)
target_link_libraries(tests PRIVATE gtest gtest_main)
target_include_directories(tests PRIVATE ${GTEST_DIR}/include src)

# Ensure pthread is linked on Linux
if (UNIX AND NOT APPLE)
    target_link_libraries(tests PRIVATE pthread)
endif()

# Register tests
add_test(NAME EmulatorTests COMMAND tests)
