cmake_minimum_required(VERSION 3.0)
project(paX11)

glob_source_files(PA_X11_SOURCES)
create_source_groups(${PA_X11_SOURCES})

add_library(paX11 ${PA_X11_SOURCES})