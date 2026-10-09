# - Find FMOD includes and library
#
# This module defines
#  FMOD_INCLUDE_DIRS
#  FMOD_LIBRARIES, the libraries to link against to use FMOD.
#  FMOD_LIBRARY_DIRS, the location of the libraries
#  FMOD_FOUND, If false, do not try to use FMOD
#
# Copyright © 2007-2008, Matt Williams
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (FMOD_LIBRARIES AND FMOD_INCLUDE_DIRS)
	SET(FMOD_FIND_QUIETLY TRUE)
ENDIF (FMOD_LIBRARIES AND FMOD_INCLUDE_DIRS)

set(_FMOD_ROOTS
	"${FMOD_SDK}"
	"$ENV{FMOD_SDK}"
	"$ENV{HOME}/FMOD Programmers API"
	"C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows"
	"$ENV{ProgramFiles}/FMOD SoundSystem/FMOD Studio API Windows"
	"/opt/fmodex")

find_path(FMOD_INCLUDE_DIRS
	NAMES fmod.hpp
	HINTS ${FMOD_INCLUDE_SEARCH_DIRS} ${INCLUDE_SEARCH_DIRS} ${_FMOD_ROOTS}
	PATH_SUFFIXES api/core/inc api/lowlevel/inc include/fmodex include fmodex
	NO_CMAKE_FIND_ROOT_PATH)

set(_FMOD_LIBRARY_SUFFIXES api/core/lib api/lowlevel/lib lib lib64)
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(_FMOD_LIBRARY_NAMES fmod_vc fmodL_vc)
		list(INSERT _FMOD_LIBRARY_SUFFIXES 0 api/core/lib/x86 api/lowlevel/lib/x86)
	else()
		set(_FMOD_LIBRARY_NAMES fmod_vc fmodL_vc fmod64_vc fmodL64_vc)
		list(INSERT _FMOD_LIBRARY_SUFFIXES 0 api/core/lib/x64 api/lowlevel/lib/x64)
	endif()
elseif(IOS OR CMAKE_SYSTEM_NAME STREQUAL "iOS")
	string(TOLOWER "${CMAKE_OSX_SYSROOT}" _FMOD_SYSROOT)
	if(_FMOD_SYSROOT MATCHES "iphonesimulator" OR
		(NOT CMAKE_OSX_SYSROOT AND CMAKE_OSX_ARCHITECTURES MATCHES "i386|x86_64"))
		set(_FMOD_LIBRARY_NAMES fmod_iphonesimulator fmodL_iphonesimulator)
	else()
		set(_FMOD_LIBRARY_NAMES fmod_iphoneos fmodL_iphoneos)
	endif()
else()
	set(_FMOD_LIBRARY_NAMES fmod fmodL)
	list(INSERT _FMOD_LIBRARY_SUFFIXES 0 "api/core/lib/${CMAKE_SYSTEM_PROCESSOR}")
endif()

if(FMOD_LIBRARY AND NOT FMOD_LIBRARIES)
	set(FMOD_LIBRARIES "${FMOD_LIBRARY}")
endif()

find_library(FMOD_LIBRARIES
	NAMES ${_FMOD_LIBRARY_NAMES}
	NAMES_PER_DIR
	HINTS ${FMOD_LIBRARY_SEARCH_DIRS} ${LIBRARY_SEARCH_DIRS} ${_FMOD_ROOTS}
	PATH_SUFFIXES ${_FMOD_LIBRARY_SUFFIXES}
	NO_CMAKE_FIND_ROOT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FMOD DEFAULT_MSG FMOD_LIBRARIES FMOD_INCLUDE_DIRS)
if(FMOD_FOUND)
	get_filename_component(FMOD_LIBRARY_DIRS "${FMOD_LIBRARIES}" DIRECTORY)
endif()
mark_as_advanced(FMOD_INCLUDE_DIRS FMOD_LIBRARIES)