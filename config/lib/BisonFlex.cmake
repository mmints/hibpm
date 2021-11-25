# Set up parser libs and dependencies
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(DeclareParser ${hibpm_source}/hibpm/declare-parser/declare.yy ${hibpm_source}/hibpm/declare-parser/declare-parser.cpp)
FLEX_TARGET(DeclareScanner ${hibpm_source}/hibpm/declare-parser/declare.l  ${hibpm_source}/hibpm/declare-parser/declare-lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(DeclareScanner DeclareParser)
