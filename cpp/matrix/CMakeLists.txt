cmake_minimum_required(VERSION 3.20)
project(matrix LANGUAGES CXX)

# -std=c++23 rather than the gnu++23 dialect CMake picks by default.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Writes build/compile_commands.json, where clangd reads each file's flags.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(matrix_tests matrix.cpp matrix_tests.cpp)

# Debug info and sanitizers, so memory bugs stop at the line that caused them.
target_compile_options(matrix_tests PRIVATE -g -Wall -Wextra -fsanitize=address,undefined)
target_link_options(matrix_tests PRIVATE -fsanitize=address,undefined)
