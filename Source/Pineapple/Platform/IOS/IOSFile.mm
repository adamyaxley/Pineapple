//
//  paIOSFile.cpp
//  paIOS
//
//  Created by apple on 05/08/2014.
//  Copyright (c) 2014 Pineapple. All rights reserved.
//

#include <Pineapple/Core/Platform/paFile.hpp>
#include <Pineapple/Platform/IOS/paIOSBridge.h>
#import <Foundation/Foundation.h>

namespace
{
	std::string makeInternalPath(const char* path)
	{
		std::string root = paIOSBridge::getRoot();
		root += "/Internal/";
		root += path;
		return root;
	}
}

// Opens a file from path and reads the contents into buffer if not null and also determines the file size and puts it into length
paFileEnum paFile::read(const char* path, unsigned char* buffer)
{
	return readStandard(paIOSBridge::makeAssetPath(path).c_str(), buffer);
}

// Gets the file size of the file located at path and writes it to size
paFileEnum paFile::getSize(const char* path, unsigned int* size)
{
	return getSizeStandard(paIOSBridge::makeAssetPath(path).c_str(), size);
}

paFileEnum paFile::getSizeInternal(const char* path, unsigned int* size)
{
	return getSizeStandard(makeInternalPath(path).c_str(), size);
}

paFileEnum paFile::readInternal(const char* path, unsigned char* buffer)
{
	return readStandard(makeInternalPath(path).c_str(), buffer);
}

paFileEnum paFile::writeInternal(const char* path, unsigned char* buffer, int size)
{
	return writeStandard(makeInternalPath(path).c_str(), buffer, size);
}