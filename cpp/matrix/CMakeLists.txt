cmake_minimum_required(VERSION 3.20)
project(matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(matrix matrix.cpp)
target_compile_options(matrix PRIVATE -g -Wall -Wextra)
