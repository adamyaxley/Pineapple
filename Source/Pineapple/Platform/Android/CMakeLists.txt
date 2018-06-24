cmake_minimum_required(VERSION 3.0)
project(paAndroid)

glob_source_files(PA_ANDROID_SOURCES)
create_source_groups(${PA_ANDROID_SOURCES})

add_library(paAndroid ${PA_ANDROID_SOURCES})
target_include_directories(paAndroid PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)
add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)