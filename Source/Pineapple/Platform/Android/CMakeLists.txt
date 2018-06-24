cmake_minimum_required(VERSION 3.0)
project(paAndroid)

glob_source_files(PA_ANDROID_SOURCES)
create_source_groups(${PA_ANDROID_SOURCES})

add_library(paAndroid ${PA_ANDROID_SOURCES})