set(hibpm_config_lib ${hibpm_config}/lib)
set(hibpm_lib_path ${PROJECT_SOURCE_DIR}/${hibpm_lib})

list(APPEND hipbm_definitions _USE_MATH_DEFINES)

# some formatted printing
set(hibpm_config_msg " - Library: ")

# load dependencies via separate cmake file
include(${hibpm_config_lib}/BisonFlex.cmake)
include(${hibpm_config_lib}/EvalMaxSAT.cmake)