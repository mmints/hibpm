if (EXISTS "${hibpm_lib_path}/EvalMaxSAT")
    add_subdirectory(${hibpm_lib}/EvalMaxSAT/lib/EvalMaxSAT) # This is the path to the library

    list(APPEND hibpm_libraries EvalMaxSAT)
    
    # Add include path of EvalMaxSAT
    list(APPEND hibpm_includes ${hibpm_lib_path}/EvalMaxSAT/lib/EvalMaxSAT/src)

    # Add include path of EvalMaxSAT dependencies
    list(APPEND hibpm_includes ${hibpm_lib_path}/EvalMaxSAT/lib/MaLib/src)
    list(APPEND hibpm_includes ${hibpm_lib_path}/EvalMaxSAT/lib/glucose/src)

    message(${hibpm_config_msg} " FOUND: EvalMaxSAT")
else()
    message(WARNING "EvalMaxSAT is required..! Update the submodules!")
endif ()