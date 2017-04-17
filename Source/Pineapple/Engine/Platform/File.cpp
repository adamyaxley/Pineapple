/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

namespace
{
	pa::File::Result openFile(FILE** file, const char* path, const char* mode)
	{
#ifdef _MSC_VER
		fopen_s(file, path, mode);
#else
		*file = fopen(path, mode);
#endif

		if (!*file)
		{
			switch (errno)
			{
			case ENOENT:
				// No such file or directory
				return pa::File::Result::NotFound;
				break;
			case EIO:
				// I/O Error
				return pa::File::Result::ReadError;
				break;
			case EACCES:
				// Permissions
				return pa::File::Result::AccessDenied;
				break;
			case ENAMETOOLONG:
				// File name is too long
				return pa::File::Result::NameTooLong;
				break;
			default:
				// Cannot find error
				return pa::File::Result::NotFound;
				break;
			}
		}

		return pa::File::Result::Success;
	}
}

const char* pa::File::getResultString(pa::File::Result result)
{
	switch (result)
	{
	case pa::File::Result::Success: return "Success";
	case pa::File::Result::NotFound: return "File not found";
	case pa::File::Result::ReadError: return "File read error";
	case pa::File::Result::IOError: return "File I/O error";
	case pa::File::Result::AccessDenied: return "Access denied";
	case pa::File::Result::NameTooLong: return "File name too long";
	case pa::File::Result::WriteError: return "File write error";
	default:
	case pa::File::Result::UnknownError: return "Unknown file error";
	}

	PA_ASSERTF(false, "Result string not implemented");
}

pa::File::Result pa::File::readStandard(const char* path, unsigned char* buffer)
{
	FILE* file;

	{
		pa::File::Result result = openFile(&file, path, "rb");

		if (result != pa::File::Result::Success)
		{
			// Cannot open the file so return error code
			return result;
		}
	}

	// obtain file size
	fseek(file, 0, SEEK_END);
	long length;
	length = ftell(file);
	rewind(file);

	if (buffer != nullptr)
	{
		// Copy the file into the buffer:
		unsigned int result;
		result = fread(buffer, 1, length, file);
		if (result != length)
		{
			fclose(file);
			return pa::File::Result::ReadError;
		}
	}
	else
	{
		fclose(file);
		return pa::File::Result::Success;
	}

	fclose(file);
	return pa::File::Result::Success;
}

pa::File::Result pa::File::writeStandard(const char* path, unsigned char* buffer, int size)
{
	FILE* file;

	{
		pa::File::Result result = openFile(&file, path, "wb");

		if (result != pa::File::Result::Success)
		{
			// Cannot open the file so return error code
			return result;
		}
	}

	int count = fwrite(buffer, sizeof(unsigned char), size, file);

	if (count != size)
	{
		return pa::File::Result::WriteError;
	}

	fclose(file);
	return pa::File::Result::Success;
}

pa::File::Result pa::File::getSizeStandard(const char* path, unsigned int* size)
{
	FILE* file;

	pa::File::Result result = openFile(&file, path, "rb");

	if (result != pa::File::Result::Success)
	{
		// Cannot open the file so return error code
		return result;
	}

	// obtain file size
	fseek(file, 0, SEEK_END);
	*size = (unsigned int)ftell(file);
	fclose(file);

	return pa::File::Result::Success;
}

pa::File::Result pa::File::readString(const char* path, std::string& contents)
{
	unsigned int size;
	pa::File::Result result;

	// Get the file size
	result = pa::File::getSize(path, &size);

	if (result != pa::File::Result::Success)
	{
		return result;
	}

	// Allocate our buffer
	unsigned char* buffer = (unsigned char*)pa::Memory::allocate(size + 1);

	// Read in the data
	result = pa::File::read(path, buffer);
	if (result != pa::File::Result::Success)
	{
		return result;
	}

	buffer[size] = '\0'; // Null terminate
	contents = (char*)buffer;

	pa::Memory::deallocate(buffer);
	return pa::File::Result::Success;
}

pa::File::Result pa::File::readStringInternal(const char* path, std::string& contents)
{
	unsigned int size;
	pa::File::Result result;

	// Get the file size
	result = pa::File::getSizeInternal(path, &size);

	if (result != pa::File::Result::Success)
	{
		return result;
	}

	// Allocate our buffer
	unsigned char* buffer = (unsigned char*)pa::Memory::allocate(size + 1);

	// Read in the data
	result = pa::File::readInternal(path, buffer);
	if (result != pa::File::Result::Success)
	{
		return result;
	}

	buffer[size] = '\0'; // Null terminate
	contents = (char*)buffer;

	pa::Memory::deallocate(buffer);
	return pa::File::Result::Success;
}

pa::File::Result pa::File::writeStringInternal(const char* path, const std::string& contents)
{
	char* cstr = const_cast<char*>(contents.c_str());
	unsigned char* buffer = reinterpret_cast<unsigned char*>(cstr);

	return pa::File::writeInternal(path, buffer, contents.length());
}
