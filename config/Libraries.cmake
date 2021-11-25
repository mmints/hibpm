set(hibpm_lib_path ${PROJECT_SOURCE_DIR}/${hibpm_lib})

list(APPEND hipbm_definitions _USE_MATH_DEFINES)

# some formatted printing
set(hibpm_config_msg " - Library: ")

# Set up parser libs and dependencies
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(DeclareParser ${hibpm_source}/hibpm/declare-parser/declare.yy ${hibpm_source}/hibpm/declare-parser/declare-parser.cpp)
FLEX_TARGET(DeclareScanner ${hibpm_source}/hibpm/declare-parser/declare.l  ${hibpm_source}/hibpm/declare-parser/declare-lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(DeclareScanner DeclareParser)

# load dependencies via separate cmake file
# include(${hibpm_config_lib}/EvalMaxSAT.cmake)
