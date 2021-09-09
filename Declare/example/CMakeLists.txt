cmake_minimum_required(VERSION 3.19) # Currently the newest version of CMake

# There are errors in compilation while using Apples Clang.
# CLion uses by default gcc-10 and g++-10.

# Explicitly change the compiler in CMake -> Not recomended, but I'm lazy
set(CMAKE_C_COMPILER "gcc-10")
set(CMAKE_CXX_COMPILER "g++-10")

project(declare-ds-example)

add_executable(declare-ds-example
        main.cpp
        ../Declare.cpp
)
