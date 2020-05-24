cmake_minimum_required(VERSION 3.0)
project(paOpenGL)

glob_source_files(PA_OPENGL_SOURCES)
create_source_groups(${PA_OPENGL_SOURCES})

list(APPEND PA_OPENGL_SOURCES ${PA_ROOT}/Ext/glad/OpenGL4.1/src/glad.c)
source_group(glad ${PA_ROOT}/Ext/glad/OpenGL4.1/src/glad.c)

add_library(paOpenGL ${PA_OPENGL_SOURCES})

set_property(TARGET paOpenGL APPEND PROPERTY INCLUDE_DIRECTORIES ${PA_ROOT}/Ext/glad/OpenGL4.1/include)

if (ANDROID OR IOS)
    glob_source_files(PA_OPENGLES1_SOURCES)
    create_source_groups(${PA_OPENGLES1_SOURCES})
    
    add_library(paOpenGLES1 ${PA_OPENGLES1_SOURCES})
    
    set_property(TARGET paOpenGLES1 APPEND PROPERTY COMPILE_DEFINITIONS PA_OPENGLES1)
endif()