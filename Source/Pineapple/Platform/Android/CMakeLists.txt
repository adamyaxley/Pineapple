cmake_minimum_required(VERSION 3.0)
project(paAndroid)

glob_source_files(PA_ANDROID_SOURCES)
create_source_groups(${PA_ANDROID_SOURCES})

list(APPEND PA_ANDROID_SOURCES ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
source_group(native_app_glue ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library(paAndroid ${PA_ANDROID_SOURCES})
set_property(TARGET paAndroid APPEND PROPERTY INCLUDE_DIRECTORIES ${ANDROID_NDK}/sources/android/native_app_glue)

if(DEFINED ANDROID_GAME_LIB)
    set_property(TARGET paAndroid APPEND PROPERTY INCLUDE_DIRECTORIES ${ANDROID_GAME_INCLUDE_DIRS})
    set_property(TARGET paAndroid APPEND PROPERTY COMPILE_DEFINITIONS PA_ANDROID_SWAPPY)
endif()