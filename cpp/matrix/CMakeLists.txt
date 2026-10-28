cmake_minimum_required(VERSION 3.20)
project(matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(matrix_tests matrix.cpp matrix_tests.cpp)
target_compile_options(matrix_tests PRIVATE -g -Wall -Wextra -fsanitize=address,undefined)
target_link_options(matrix_tests PRIVATE -fsanitize=address,undefined)
