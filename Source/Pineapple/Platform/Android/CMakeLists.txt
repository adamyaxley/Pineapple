cmake_minimum_required(VERSION 3.0)
project(paAndroid)

glob_source_files(PA_ANDROID_SOURCES)
create_source_groups(${PA_ANDROID_SOURCES})

list(APPEND PA_ANDROID_SOURCES ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
source_group(native_app_glue ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library(paAndroid ${PA_ANDROID_SOURCES})
target_include_directories(paAndroid PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)