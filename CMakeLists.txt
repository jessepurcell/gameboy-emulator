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

# Add your emulator executable
add_executable(emulator src/main.cpp ${SRC_FILES})
target_include_directories(emulator PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Enable testing
enable_testing()

# Add Google Test
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/third_party/googletest")
add_subdirectory(${GTEST_DIR})

# Loop through all test files and create separate test executables
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Create an executable for each test file (WITHOUT `main.cpp`)
    add_executable(${TEST_NAME} ${TEST_FILE} ${SRC_FILES})

    # Include the necessary directories
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

    # Link against GoogleTest
    target_link_libraries(${TEST_NAME} gtest gtest_main pthread)

    # Register the test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
