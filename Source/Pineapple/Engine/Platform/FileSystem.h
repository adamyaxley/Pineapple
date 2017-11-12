#pragma once

#include <Pineapple/Engine/Platform/PlatformSettings.h>
#include <chrono>

namespace pa
{
	class FileSystem;

	namespace MakeInternal
	{
		std::unique_ptr<FileSystem> fileSystem(PlatformSettings::FileSystem settings);
	}

	enum class FileStorage
	{
		EngineAsset,
		UserAsset,
		Internal
	};

	enum class FileResult
	{
		Success,
		NotFound,
		ReadError,
		IOError,
		AccessDenied,
		NameTooLong,
		WriteError
	};

	class FileBuffer
	{
	public:
		void allocate(std::size_t size);
		std::unique_ptr<unsigned char[]>& getBuffer();
		const std::unique_ptr<unsigned char[]>& getBuffer() const;
		std::size_t getSize() const;
		std::string createString() const;

	private:
		std::unique_ptr<unsigned char[]> m_buffer;
		std::size_t m_size{ 0 };
	};

	class FilePath
	{
	public:
		FilePath(const FileSystem& fileSystem, FileStorage storage, const std::string& path);

		const std::string& asString() const;

		FileResult read(FileBuffer& buffer) const;

		FileResult write(const FileBuffer& buffer) const;

		FileResult getModificationTime(std::chrono::system_clock::time_point& modificationTime) const;

	private:
		const FileSystem& m_fileSystem;
		const std::string m_path;
	};

	// Overridable virtual functions for special platform
	class FileSystem
	{
	public:
		FileSystem(PlatformSettings::FileSystem settings);
		FileSystem(const FileSystem&) = default;
		FileSystem(FileSystem&&) = default;

		static const char* getResultString(FileResult result);

		const PlatformSettings::FileSystem& getSettings() const;

		virtual FileResult read(const FilePath& path, FileBuffer& buffer) const;

		virtual FileResult write(const FilePath& path, const FileBuffer& buffer) const;

		virtual FileResult getModificationTime(const FilePath& path, std::chrono::system_clock::time_point& modificationTime) const;

	private:

		const PlatformSettings::FileSystem m_settings;
	};
}