cmake_minimum_required(VERSION 3.0)
project(Simple)

glob_source_files(SIMPLE_SOURCES)
create_source_groups(${SIMPLE_SOURCES})

add_pineapple_app(Simple ${SIMPLE_SOURCES})