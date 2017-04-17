cmake_minimum_required(VERSION 3.0)
project(CatchTheClown)

glob_source_files(CATCHTHECLOWN_SOURCES)
create_source_groups(${CATCHTHECLOWN_SOURCES})

add_pineapple_app(CatchTheClown ${CATCHTHECLOWN_SOURCES})