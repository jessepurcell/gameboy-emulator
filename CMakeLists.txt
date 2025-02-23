cmake_minimum_required(VERSION 3.14)
project(GameBoyEmulator)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source files
set(SOURCES
    src/main.cpp
    src/cpu.cpp
    src/memory.cpp
    src/emulator.cpp
)

# Create an executable target for the emulator
add_executable(gameboy-emulator ${SOURCES})

# GoogleTest setup
enable_testing()
add_subdirectory(third_party/googletest)
add_subdirectory(tests)

# Link GoogleTest with the test runner
target_link_libraries(gameboy-emulator PRIVATE gtest gtest_main)
