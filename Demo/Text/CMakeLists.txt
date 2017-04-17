cmake_minimum_required(VERSION 3.0)
project(Text)

glob_source_files(TEXT_SOURCES)
create_source_groups(${TEXT_SOURCES})

add_pineapple_app(Text ${TEXT_SOURCES})