cmake_minimum_required(VERSION 3.0)
project(HelloWorld)

glob_source_files(HELLO_WORLD_SOURCES)
create_source_groups(${HELLO_WORLD_SOURCES})

add_executable(HelloWorld ${HELLO_WORLD_SOURCES})
target_link_libraries(HelloWorld paEngine)