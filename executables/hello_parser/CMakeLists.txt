cmake_minimum_required(VERSION 3.19) # Currently the newest version of CMake
project(hello_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello_parser main.cpp)

target_include_directories(hello_parser SYSTEM BEFORE PRIVATE ${hibpm_include} ${hibpm_includes})

target_link_libraries(hello_parser hibpm ${hibpm_libraries} ${LDFLAGS}) # In the CMake documentation it's said that the variable should be FLEX_LIBRARIES.
                                                                        # But in my case I'm using the variable which I've set in the .zshrc and it seems to work.