cmake_minimum_required(VERSION 3.0)
project(paSoundPool)

glob_source_files(PA_SOUNDPOOL_SOURCES)
create_source_groups(${PA_SOUNDPOOL_SOURCES})

add_library(paSoundPool ${PA_SOUNDPOOL_SOURCES})
target_include_directories(paSoundPool PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)