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

#UNSET(FMOD_INCLUDE_SEARCH_DIRS CACHE)
#UNSET(FMOD_LIBRARY_SEARCH_DIRS CACHE)

SET(FMOD_INCLUDE_SEARCH_DIRS
	${INCLUDE_SEARCH_DIRS}
	${CMAKE_INCLUDE_PATH}
	/usr/include
	/usr/local/include
	/usr/include/fmodex
	/usr/local/include/fmodex
	/opt/include/fmodex
	/opt/fmodex/include
	"C:\\Program Files (x86)\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\lowlevel\\inc"
	"~/FMOD\ Programmers\ API/api/core/inc"
	CACHE STRING ""
)

SET(FMOD_LIBRARY_SEARCH_DIRS
	${LIBRARY_SEARCH_DIRS}
	${CMAKE_LIBRARY_PATH}
	/usr/lib
	/usr/lib64
	/usr/local/lib
	/usr/local/lib64
	/opt/lib
	/opt/lib64
	/opt/fmodex/lib
	/opt/fmodex/lib64
	"C:\\Program Files (x86)\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\lowlevel\\lib"
	"~/FMOD\ Programmers\ API/api/core/lib"
	CACHE STRING ""
)

IF (NOT FMOD_FIND_QUIETLY)
	MESSAGE(STATUS "Looking for FMOD")
ENDIF (NOT FMOD_FIND_QUIETLY)
FIND_PATH(FMOD_INCLUDE_DIRS fmod.hpp ${FMOD_INCLUDE_SEARCH_DIRS})
MESSAGE(STATUS "FMOD_INCLUDE_DIRS: " ${FMOD_INCLUDE_DIRS})
IF(WIN32)
	IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
		# 32 bit
		MESSAGE(STATUS "Looking for Win32 libs")
		FIND_LIBRARY(FMOD_LIBRARIES fmod_vc fmodL_vc ${FMOD_LIBRARY_SEARCH_DIRS})
	ELSE()
		# 64 bit
		MESSAGE(STATUS "Looking for X64 libs")
		FIND_LIBRARY(FMOD_LIBRARIES fmod64_vc fmodL64_vc ${FMOD_LIBRARY_SEARCH_DIRS})
	ENDIF()
ELSEIF(IOS AND CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
	MESSAGE(STATUS "Looking for IPhoneOS Simulator libs")
	FIND_LIBRARY(FMOD_LIBRARIES fmod_iphonesimulator fmodL_iphonesimulator ${FMOD_LIBRARY_SEARCH_DIRS})
ELSEIF(IOS)
	MESSAGE(STATUS "Looking for IPhoneOS libs")
	FIND_LIBRARY(FMOD_LIBRARIES fmod_iphoneos fmodL_iphoneos ${FMOD_LIBRARY_SEARCH_DIRS})
ELSEIF(UNIX)
	MESSAGE(STATUS "Looking for Unix libs")
	FIND_LIBRARY(FMOD_LIBRARIES fmod fmodL ${FMOD_LIBRARY_SEARCH_DIRS})
ENDIF()
SET(FMOD_LIBRARIES ${FMOD_LIBRARY})

#Do some preparation

SET(FMOD_INCLUDE_DIRS ${FMOD_INCLUDE_DIRS})
SET(FMOD_LIBRARIES ${FMOD_LIBRARIES})
SET(FMOD_LIBRARY_DIRS ${FMOD_LIBRARY_DIRS})

MARK_AS_ADVANCED(FMOD_INCLUDE_DIRS FMOD_LIBRARIES FMOD_LIBRARY_DIRS)

IF (FMOD_INCLUDE_DIRS AND FMOD_LIBRARIES)
	SET(FMOD_FOUND TRUE)
ENDIF (FMOD_INCLUDE_DIRS AND FMOD_LIBRARIES)

IF (FMOD_FOUND)
	IF (NOT FMOD_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${FMOD_LIBRARIES} from ${FMOD_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes  : ${FMOD_INCLUDE_DIRS}")
	ENDIF (NOT FMOD_FIND_QUIETLY)
ELSE (FMOD_FOUND)
	MESSAGE(STATUS "fmod not found!")
	IF (FMOD_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find FMOD. Make sure you have the FMOD development headers are installed. Otherwise, try setting LIBRARY_SEARCH_DIRS and INCLUDE_SEARCH_DIRS to the place FMOD was installed with -DLIBRARY_SEARCH_DIRS=<path/to/lib> -DINCLUDE_SEARCH_DIRS=<path/to/include>")
	ENDIF (FMOD_FIND_REQUIRED)
ENDIF (FMOD_FOUND)