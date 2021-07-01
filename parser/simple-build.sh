# This script can be used for now to build the parser.
# In future it will be replaced by a proper workling cmake.

bison declare.yy -o declare-parser.cpp
flex -o declare-lexer.c declare.l 
g++-10 -o declare-parser main.cpp declare-parser.cpp declare-lexer.c Declare/Declare.cpp