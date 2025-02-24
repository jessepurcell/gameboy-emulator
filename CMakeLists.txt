# Set minimum CMake version and project
cmake_minimum_required(VERSION 3.16)
project(GameboyEmulator)

# Enable C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files in `src/`, but EXCLUDE `main.cpp`
file(GLOB SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Collect all test files in `tests/`
file(GLOB TEST_FILES tests/*.cpp)

# Add a library for the shared code
add_library(emulator-lib STATIC ${SRC_FILES})
target_include_directories(emulator-lib PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Add the emulator executable
add_executable(emulator src/main.cpp)
target_link_libraries(emulator PRIVATE emulator-lib)

# Enable testing
enable_testing()

# Add GoogleTest (if using git submodule)
add_subdirectory(third_party/googletest)  # Change path as needed

# Add the test executable
add_executable(runTests tests/test_cpu.cpp tests/test_memory.cpp)
target_link_libraries(runTests PRIVATE emulator-lib gtest_main)

# Register tests (makes them visible in VS Code)
include(GoogleTest)
gtest_discover_tests(runTests)
