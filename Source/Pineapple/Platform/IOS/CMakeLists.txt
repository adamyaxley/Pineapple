cmake_minimum_required(VERSION 3.0)
project(paIOS)

glob_source_files(PA_IOS_SOURCES)
create_source_groups(${PA_IOS_SOURCES})

add_library(paIOS ${PA_IOS_SOURCES})
set_target_properties(paIOS PROPERTIES
    LINKER_LANGUAGE CXX
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)