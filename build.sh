# This script can be used for now to build the parser.
# In future it will be replaced by a proper workling cmake.

sh clear.sh # Remove generated Bison and Flex Files
bison declare.yy -o declare-parser.cpp # Generates a Bison Class from the Bison File
flex -o declare-lexer.c declare.l # Generates a Flex C File from Flex file
g++-10 -o declare-parser main.cpp declare-parser.cpp declare-lexer.c Declare/Declare.cpp # Build