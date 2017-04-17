cmake_minimum_required(VERSION 3.0)
project(paOpenGL)

glob_source_files(PA_OPENGL_SOURCES)
create_source_groups(${PA_OPENGL_SOURCES})

add_library(paOpenGL ${PA_OPENGL_SOURCES})

set_property(TARGET paOpenGL APPEND PROPERTY INCLUDE_DIRECTORIES
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

set_property(TARGET paOpenGL APPEND PROPERTY COMPILE_DEFINITIONS PA_OPENGLES2)