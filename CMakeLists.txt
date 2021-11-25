cmake_minimum_required(VERSION 3.19) # Currently the newest version of CMake
project(hibpm)

set(CMAKE_CXX_STANDARD 17)

# setting up different paths
set(hibpm_config ${PROJECT_SOURCE_DIR}/config)
set(hibpm_lib lib)

set(hibpm_source ${PROJECT_SOURCE_DIR}/src)

# configure everything to use the required dependencies
include(${hibpm_config}/Libraries.cmake)

# add source files for compilation
include(${hibpm_config}/Sources.cmake)

message("-- Libraries: [ ${hibpm_libraries} ]")

# create HiBPM as static library using all source files
add_library(hibpm STATIC ${hibpm_sources})

# add include directories from dependencies as system includes
target_include_directories(hibpm SYSTEM BEFORE PRIVATE ${hibpm_includes})
message(STATUS ${hibpm_includes})

# add the own include directory for public headers
target_include_directories(hibpm BEFORE PUBLIC ${hibpm_source}) # FIXME: For now all files of the lib can be included 
message(STATUS ${hibpm_source})

# link the framework using all required libraries
target_link_libraries(hibpm ${hipbm_libraries})
message(STATUS ${hibpm_libraries})

add_subdirectory(executables)