cmake_minimum_required(VERSION 3.0)
project(paEngine)

glob_source_files(PA_ENGINE_SOURCES)
create_source_groups(${PA_ENGINE_SOURCES})

add_library(paEngine ${PA_ENGINE_SOURCES})