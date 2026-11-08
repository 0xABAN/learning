cmake_minimum_required(VERSION 3.20)
project(nn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra)
add_subdirectory(../matrix matrix)

add_executable(net micrograd/net.cpp)



