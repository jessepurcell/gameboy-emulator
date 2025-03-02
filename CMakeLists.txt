# Set minimum CMake version and project
cmake_minimum_required(VERSION 3.16)
project(GameboyEmulator)

# Enable C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files in `src/`, EXCLUDING `main.cpp`
file(GLOB SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Collect all test files in `tests/`
file(GLOB TEST_FILES tests/*.cpp)

# Add the emulator library (shared code)
add_library(emulator-lib STATIC ${SRC_FILES})
target_include_directories(emulator-lib PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Add the emulator executable (includes main.cpp)
add_executable(emulator src/main.cpp)
target_link_libraries(emulator PRIVATE emulator-lib)

# Enable testing
enable_testing()

# Add GoogleTest (if using a submodule)
add_subdirectory(third_party/googletest)  # Adjust path if necessary

# Add test executable (ONLY test files)
add_executable(runTests ${TEST_FILES})
target_link_libraries(runTests PRIVATE emulator-lib gtest_main)

# Register tests for CTest
include(GoogleTest)
gtest_discover_tests(runTests)

# Custom run commands for convenience
add_custom_target(run-emulator
    COMMAND emulator
    DEPENDS emulator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(run-tests
    COMMAND runTests
    DEPENDS runTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
