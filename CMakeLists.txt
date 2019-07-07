cmake_minimum_required(VERSION 3.1)
project(Pineapple)

option(GENERATE_DOCS "GENERATE_DOCS" OFF)
option(GENERATE_TESTS "GENERATE_TESTS" ON)
option(GENERATE_DEMOS "GENERATE_DEMOS" ON)
option(GENERATE_PLUGINS "GENERATE_PLUGINS" ON)

if (GENERATE_DEMOS AND NOT GENERATE_PLUGINS)
    message(STATUS "GENERATE_DEMOS is ON (forcing GENERATE_PLUGINS to be ON too)")
    set(GENERATE_PLUGINS ON)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(MSVC)
    add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
    add_compile_options("/MP")
endif()

if (GENERATE_TESTS)
    include(CTest)

    if (CMAKE_VERSION VERSION_LESS 3.2)
        set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
    else()
        set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
    endif()

    include(Build/CMake/DownloadProject/DownloadProject.cmake)
    download_project(PROJ                googletest
                     GIT_REPOSITORY      https://github.com/google/googletest.git
                     GIT_TAG             release-1.8.0
                     ${UPDATE_DISCONNECTED_IF_AVAILABLE}
    )

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

get_filename_component(PA_ROOT "." ABSOLUTE)
get_directory_property(hasParent PARENT_DIRECTORY)
if (hasParent)
    set(PA_ROOT ${PA_ROOT} PARENT_SCOPE)
else()
    set(PA_ROOT ${PA_ROOT})
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Build/CMake")

if (GENERATE_PLUGINS)
    if((UNIX OR WIN32) AND NOT ANDROID)
        find_package(FMOD REQUIRED)
    endif()

    if(UNIX AND NOT ANDROID)
        find_package(X11 REQUIRED)
    endif()
    
    if(ANDROID)
        find_library(LOG_LIB log)
        find_library(ANDROID_LIB android)
        find_library(EGL_LIB egl)
        find_library(GLESV1_CM_LIB GLESv1_CM)
    endif()
endif()

function(glob_source_files _SOURCES)
    get_filename_component(_src_root_path "." ABSOLUTE)
    file(
        GLOB_RECURSE _glob_sources
        LIST_DIRECTORIES false
        "${_src_root_path}/*.c*"
        "${_src_root_path}/*.h*"
        "${_src_root_path}/*.inl"
    )
    set(${_SOURCES} ${_glob_sources} PARENT_SCOPE)
endfunction()

function(create_source_groups _SOURCES)
    set( _SOURCES_LIST ${_SOURCES} ${ARGN} )
    get_filename_component(_src_root_path "." ABSOLUTE)
    foreach(_source IN ITEMS ${_SOURCES_LIST})
        get_filename_component(_source_path "${_source}" PATH)
        file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()
endfunction()

function(add_pineapple_app _TARGET _SOURCES)
    set( _SOURCES_LIST ${_SOURCES} ${ARGN} )
    
    include_directories(${PA_ROOT}/Source ${PA_ROOT}/Ext)

    if(WIN32)
        add_executable(${_TARGET} WIN32 ${_SOURCES_LIST})
        # Need to link Opengl32.lib for wgl (not sure if this is correct usage of glad)
        target_link_libraries(${_TARGET} paEngine paWindows paFMOD paOpenGL Opengl32.lib ${FMOD_LIBRARIES})
    endif()
    
    if(UNIX AND NOT ANDROID)
        add_executable(${_TARGET} ${_SOURCES_LIST})
        target_link_libraries(${_TARGET} paX11 paFMOD paOpenGL paEngine ${X11_LIBRARIES} pthread dl ${FMOD_LIBRARIES})
        set_property(TARGET ${_TARGET} APPEND PROPERTY INCLUDE_DIRECTORIES ${X11_INCLUDE_DIRS})
    endif()
    
    if(ANDROID)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
        add_library(${_TARGET} SHARED ${_SOURCES_LIST})
        target_link_libraries(${_TARGET} -Wl,--whole-archive paAndroid -Wl,--no-whole-archive paOpenGLES1 paSoundPool paEngine ${ANDROID_LIB} ${LOG_LIB} ${EGL_LIB} ${GLESV1_CM_LIB})
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/pineapple.json)
        set(PA_SETTINGS_USER_ASSETS_PATH ${CMAKE_CURRENT_LIST_DIR}/Assets)
        set(PA_SETTINGS_ENGINE_ASSETS_PATH ${PA_ROOT}/Assets)
        # Configure the settings file
        configure_file(${CMAKE_CURRENT_LIST_DIR}/pineapple.json ${CMAKE_CURRENT_BINARY_DIR}/pineapple.json)
    endif()
    
    if(WIN32)
        foreach(_library IN ITEMS ${FMOD_LIBRARIES})
            string(REPLACE "_vc.lib" ".dll" _dll ${_library})
            add_custom_command(
                TARGET ${_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${_dll}
                        ${CMAKE_CURRENT_BINARY_DIR})
        endforeach()
    endif()
endfunction()

set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:Debug>:PA_DEBUG>
)

include_directories(Source Ext)

if (GENERATE_DOCS)
    get_property(DOC_INCLUDE_DIRS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    file(
        GLOB_RECURSE DOC_HEADER_FILES
        LIST_DIRECTORIES false
        "${PA_ROOT}/Source/Pineapple/Engine/*.h*"
    )
    
    # Below functionality is for updating only a single file, but it doesn't quite work well yet because standardese can't link to other files in this mode
    #foreach(headerFile ${DOC_HEADER_FILES})
    #    get_filename_component(headerFileName ${headerFile} NAME_WE)
    #    set (docFile "${CMAKE_BINARY_DIR}/standardese_docs_engine/doc_${headerFileName}.md")
    #    if(NOT(${headerFile} IS_NEWER_THAN ${docFile}))
    #        list(REMOVE_ITEM DOC_HEADER_FILES ${headerFile})
    #    endif()
    #endforeach()
    #
    #list(LENGTH DOC_HEADER_FILES inputCount)
    #if(${inputCount} GREATER 0)
        include(C:/standardese/standardese-config.cmake)
        standardese_generate(docs_engine
                             --compilation.standard=c++14
                             INCLUDE_DIRECTORY ${DOC_INCLUDE_DIRS}
                             INPUT ${DOC_HEADER_FILES})
    #else()
    #    # Add empty target as there is nothing to do
    #    add_custom_target(standardese_docs_engine)
    #    message(STATUS "All documentation files are up-to-date")
    #endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # To be able to sort projects into folders

add_subdirectory(Source/Pineapple/Engine)
set_target_properties (paEngine PROPERTIES FOLDER Engine)

if (GENERATE_PLUGINS)
    if (WIN32)
        add_subdirectory(Source/Pineapple/Platform/Windows)
        add_subdirectory(Source/Pineapple/Graphics/OpenGL)
        add_subdirectory(Source/Pineapple/Sound/FMOD)
        set_target_properties (paWindows PROPERTIES FOLDER Plugins)
        set_target_properties (paOpenGL PROPERTIES FOLDER Plugins)
        set_target_properties (paFMOD PROPERTIES FOLDER Plugins)
    endif()

    if (UNIX AND NOT ANDROID)
        add_subdirectory(Source/Pineapple/Platform/X11)
        add_subdirectory(Source/Pineapple/Graphics/OpenGL)
        add_subdirectory(Source/Pineapple/Sound/FMOD)
        set_target_properties (paX11 PROPERTIES FOLDER Plugins)
        set_target_properties (paOpenGL PROPERTIES FOLDER Plugins)
        set_target_properties (paFMOD PROPERTIES FOLDER Plugins)
    endif()
    
    if (ANDROID)
        add_subdirectory(Source/Pineapple/Platform/Android)
        add_subdirectory(Source/Pineapple/Graphics/OpenGL)
        add_subdirectory(Source/Pineapple/Sound/SoundPool)
        set_target_properties (paAndroid PROPERTIES FOLDER Plugins)
        set_target_properties (paOpenGLES1 PROPERTIES FOLDER Plugins)
        set_target_properties (paSoundPool PROPERTIES FOLDER Plugins)
    endif()
endif()

# Tests
if (GENERATE_TESTS)
    set_target_properties (gtest PROPERTIES FOLDER Test/gtest)
    set_target_properties (gtest_main PROPERTIES FOLDER Test/gtest)
    set_target_properties (gmock PROPERTIES FOLDER Test/gtest)
    set_target_properties (gmock_main PROPERTIES FOLDER Test/gtest)
    add_subdirectory(Test/Engine)
    set_target_properties (paEngineTest PROPERTIES FOLDER Test)
endif()

# Demos
if (GENERATE_DEMOS)
    add_subdirectory(Demo/AnimatedSprite)
    add_subdirectory(Demo/SpaceRocks)
    add_subdirectory(Demo/HelloWorld)
    add_subdirectory(Demo/CatchTheClown)
    add_subdirectory(Demo/Simple)
    add_subdirectory(Demo/Text)
    set_target_properties (AnimatedSprite PROPERTIES FOLDER Demo)
    set_target_properties (SpaceRocks PROPERTIES FOLDER Demo)
    set_target_properties (HelloWorld PROPERTIES FOLDER Demo)
    set_target_properties (CatchTheClown PROPERTIES FOLDER Demo)
    set_target_properties (Simple PROPERTIES FOLDER Demo)
    set_target_properties (Text PROPERTIES FOLDER Demo)
endif()
