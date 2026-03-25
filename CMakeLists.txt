cmake_minimum_required(VERSION 4.2)

project(BoardGameProject VERSION 1.0 LANGUAGES CXX)

#SETTINGS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#WARNINGS VOOR CLANG/GCC
add_compile_options(-Wall -Wextra -Wpedantic)

#SUBDIRECTORIES
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)