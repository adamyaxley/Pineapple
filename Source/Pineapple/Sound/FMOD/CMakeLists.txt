cmake_minimum_required(VERSION 3.0)
project(paFMOD)

glob_source_files(PA_FMOD_SOURCES)
create_source_groups(${PA_FMOD_SOURCES})

add_library(paFMOD ${PA_FMOD_SOURCES})

set_property(TARGET paFMOD APPEND PROPERTY INCLUDE_DIRECTORIES
    ${FMOD_INCLUDE_DIRS}
)