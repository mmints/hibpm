cmake_minimum_required(VERSION 3.19) # Currently the newest version of CMake

project(declare_parser)

# Find Libs
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# Set Targest
# Will this be done automatically with Flex and Bison?
BISON_TARGET(DeclareParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c) 
FLEX_TARGET(DeclareScanner scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
ADD_FLEX_BISON_DEPENDENCY(DeclareScanner DeclareParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}) # For now no source directory

add_executable(declare_parser
   main.c
   ${BISON_DeclareParser_OUTPUTS}
   ${FLEX_DeclareScanner_OUTPUTS}
)
target_link_libraries(declare_parser ${LDFLAGS}) # In the CMake documentation it's said that the variable should be FLEX_LIBRARIES.
                                                 # But in my case I'm using the variable which I've set in the .zshrc and it seems to work.