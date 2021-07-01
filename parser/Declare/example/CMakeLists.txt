cmake_minimum_required(VERSION 3.19) # Currently the newest version of CMake

# There are errors in compilation while using Apples Clang.
# CLion uses by default gcc-10 and g++-10.

project(declare-ds-example)

add_executable(declare-ds-example
        main.cpp
        ../Declare.cpp
        ../Declare.hh
)
