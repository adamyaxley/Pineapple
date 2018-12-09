#pragma once
#include <Pineapple/Engine/Platform/FileSystem.h>

namespace pa
{
	class AndroidFileSystem : public pa::FileSystem
	{
	public:
		AndroidFileSystem(PlatformSettings::FileSystem settings);

		FileResult read(const FilePath& path, FileBuffer& buffer) const override;

		FileResult write(const FilePath& path, const FileBuffer& buffer) const override;

		FileResult getModificationTime(const FilePath& path, std::chrono::system_clock::time_point& modificationTime) const override;
	};
}