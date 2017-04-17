cmake_minimum_required(VERSION 3.0)

project(paEngineTest)

glob_source_files(PA_ENGINETEST_SOURCES)
add_executable(paEngineTest ${PA_ENGINETEST_SOURCES})
target_link_libraries(paEngineTest paEngine gtest gmock_main)

add_test(NAME EngineTest COMMAND paEngineTest)
