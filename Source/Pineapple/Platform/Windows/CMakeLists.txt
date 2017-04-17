cmake_minimum_required(VERSION 3.0)
project(paWindows)

glob_source_files(PA_WINDOWS_SOURCES)
create_source_groups(${PA_WINDOWS_SOURCES})

add_library(paWindows ${PA_WINDOWS_SOURCES})