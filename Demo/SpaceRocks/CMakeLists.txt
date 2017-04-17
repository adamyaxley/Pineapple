cmake_minimum_required(VERSION 3.0)
project(SpaceRocks)

glob_source_files(SPACEROCKS_SOURCES)
create_source_groups(${SPACEROCKS_SOURCES})

add_pineapple_app(SpaceRocks ${SPACEROCKS_SOURCES})