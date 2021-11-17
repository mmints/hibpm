cmake_minimum_required(VERSION 3.19) # Currently the newest version of CMake
project(declare_parser)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER "g++-10")
set(CMAKE_CXX_COMPILER "g++-10")

# Find Libs
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# Set Targets
# Will this be done automatically with Flex and Bison?
BISON_TARGET(DeclareParser declare.yy ${CMAKE_CURRENT_BINARY_DIR}/declare-parser.cpp)
FLEX_TARGET(DeclareScanner declare.l ${CMAKE_CURRENT_BINARY_DIR}/declare-lexer.c)
ADD_FLEX_BISON_DEPENDENCY(DeclareScanner DeclareParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}) # For now no source directory

add_executable(declare_parser
        main.cpp
        Parser.cpp
        Declare/Declare.cpp
        Automaton/Automaton.cpp

        Process/Process.cpp
        Process/State.cpp

        Process/Unary.cpp
        Process/Unary/Participation.cpp
        Process/Unary/AtMostOne.cpp
        Process/Unary/Init.cpp
        Process/Unary/End.cpp

        Process/Binary.cpp
        Process/Binary/RespondedExistence.cpp
        Process/Binary/Response.cpp
        Process/Binary/AlternatedResponse.cpp
        Process/Binary/ChainResponse.cpp
        Process/Binary/Precedence.cpp
        Process/Binary/AlternatedPrecedence.cpp
        Process/Binary/ChainPrecedence.cpp
        Process/Binary/CoExistence.cpp
        Process/Binary/Succession.cpp
        Process/Binary/AlternateSuccession.cpp
        Process/Binary/ChainSuccession.cpp
        Process/Binary/NotChainSuccession.cpp
        Process/Binary/NotSuccession.cpp
        Process/Binary/NotCoExistence.cpp

        Repair/RepairAutomata.cpp

        ${BISON_DeclareParser_OUTPUTS}
        ${FLEX_DeclareScanner_OUTPUTS}
        Automaton/TopoGraph.cpp Automaton/TopoGraph.h)

target_link_libraries(declare_parser ${LDFLAGS}) # In the CMake documentation it's said that the variable should be FLEX_LIBRARIES.
                                                 # But in my case I'm using the variable which I've set in the .zshrc and it seems to work.