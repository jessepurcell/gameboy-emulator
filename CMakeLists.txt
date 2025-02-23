cmake_minimum_required(VERSION 3.16)
project(GameboyEmulator)

# Enable C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SDL3 submodule
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/third_party/SDL")
add_subdirectory(${SDL3_DIR} EXCLUDE_FROM_ALL)

# Add Google Test submodule
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/third_party/googletest")
add_subdirectory(${GTEST_DIR})

# Add your emulator executable
add_executable(emulator src/main.cpp)
target_link_libraries(emulator PRIVATE SDL3::SDL3-static)

# Add unit tests
# add_executable(tests tests/test_cpu.cpp)
# target_link_libraries(tests PRIVATE gtest gtest_main)

# Enable CTest to allow running `ctest`
enable_testing()
# add_test(NAME EmulatorTests COMMAND tests)
