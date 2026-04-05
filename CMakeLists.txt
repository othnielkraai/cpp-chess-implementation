cmake_minimum_required(VERSION 4.2)

project(Run-Chess_API VERSION 1.0 LANGUAGES CXX)

#SETTINGS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_COMMANDS ON)

#WARNINGS VOOR CLANG/GCC
add_compile_options(-Wall -Wextra -Wpedantic)

#SUBDIRECTORIES
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)