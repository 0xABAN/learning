cmake_minimum_required(VERSION 3.20)
project(matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-g -Wall -Wextra -fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

add_library(matrix matrix.cpp)

add_executable(matrix_tests matrix_tests.cpp)
target_link_libraries(matrix_tests PRIVATE matrix)
