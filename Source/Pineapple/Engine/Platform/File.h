/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <chrono>
#include <string>

namespace pa
{
	namespace File
	{
		enum class Result
		{
			Success,
			NotFound,
			ReadError,
			IOError,
			AccessDenied,
			NameTooLong,
			UnknownError,
			WriteError
		};

		// Initialises the file system
		extern bool init();

		// Opens a file from path and reads the contents into buffer if not null and also determines the file size and
		// puts it into length
		extern Result read(const char* path, unsigned char* buffer);

		// Gets the file size of the file located at path and writes it to size
		extern Result getSize(const char* path, unsigned int* size);

		extern Result getSizeInternal(const char* path, unsigned int* size);
		extern Result readInternal(const char* path, unsigned char* buffer);
		extern Result writeInternal(const char* path, unsigned char* buffer, int size);

		extern Result getModificationTime(const char* path, std::chrono::system_clock::time_point& secondsSinceEpoch);

		extern std::string getAssetsPath();

		Result getSizeStandard(const char* path, unsigned int* size);
		Result readStandard(const char* path, unsigned char* buffer);
		Result writeStandard(const char* path, unsigned char* buffer, int size);

		// Gets the error string of the result
		const char* getResultString(Result result);

		Result readString(const char* path, std::string& contents);
		Result readStringInternal(const char* path, std::string& contents);
		Result writeStringInternal(const char* path, const std::string& contents);
	}
}
