/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

namespace
{
	std::string makeInternalPath(const char* path)
	{
		std::ostringstream stream;
		stream << "Internal/" << path;

		return stream.str();
	}

	std::string makeAssetsPath(const char* path)
	{
		std::ostringstream stream;
		stream << "Assets/" << path;

		return stream.str();
	}
}

bool pa::File::init()
{
	// Find the current path of the executable
	// char* path;
	//_get_pgmptr(&path);

	return true;
}

pa::File::Result pa::File::read(const char* path, unsigned char* buffer)
{
	return readStandard(makeAssetsPath(path).c_str(), buffer);
}

pa::File::Result pa::File::getSize(const char* path, unsigned int* size)
{
	return getSizeStandard(makeAssetsPath(path).c_str(), size);
}

pa::File::Result pa::File::getSizeInternal(const char* path, unsigned int* size)
{
	return getSizeStandard(makeInternalPath(path).c_str(), size);
}

pa::File::Result pa::File::readInternal(const char* path, unsigned char* buffer)
{
	return readStandard(makeInternalPath(path).c_str(), buffer);
}

pa::File::Result pa::File::writeInternal(const char* path, unsigned char* buffer, int size)
{
	return writeStandard(makeInternalPath(path).c_str(), buffer, size);
}

pa::File::Result pa::File::getModificationTime(const char* path,
											   std::chrono::system_clock::time_point& modificationTime)
{
	struct stat st;
	int ret = stat(makeAssetsPath(path).c_str(), &st);

	if (ret == -1)
	{
		return pa::File::Result::UnknownError;
	}
	else
	{
		modificationTime = std::chrono::system_clock::from_time_t(st.st_mtime);
		return pa::File::Result::Success;
	}
}

std::string pa::File::getAssetsPath()
{
	return makeAssetsPath("");
}