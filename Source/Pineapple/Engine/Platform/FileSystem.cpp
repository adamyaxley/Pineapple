#include <Pineapple/Engine/Platform/FileSystem.h>
#include <Pineapple/Engine/Platform/Memory.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <cerrno>
#include <cstdio>
#include <mutex>
#include <sys/stat.h>
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

namespace
{
	pa::FileResult openFile(FILE** file, const char* path, const char* mode)
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
				return pa::FileResult::NotFound;
				break;
			case EIO:
				// I/O Error
				return pa::FileResult::ReadError;
				break;
			case EACCES:
				// Permissions
				return pa::FileResult::AccessDenied;
				break;
			case ENAMETOOLONG:
				// File name is too long
				return pa::FileResult::NameTooLong;
				break;
			default:
				// Cannot find error
				return pa::FileResult::NotFound;
				break;
			}
		}

		return pa::FileResult::Success;
	}
}

void pa::FileBuffer::allocate(std::size_t size)
{
	PA_ASSERTF(m_size == 0, "Buffer has already been allocated");
	m_buffer = std::make_unique<unsigned char[]>(size);
	m_size = size;
}

std::unique_ptr<unsigned char[]>& pa::FileBuffer::getBuffer()
{
	return m_buffer;
}

const std::unique_ptr<unsigned char[]>& pa::FileBuffer::getBuffer() const
{
	return m_buffer;
}

std::size_t pa::FileBuffer::getSize() const
{
	return m_size;
}

std::string pa::FileBuffer::createString() const
{
	std::string string((char*)m_buffer.get(), m_size);
	return string;
}

void pa::FileBuffer::copyFromString(std::string string)
{
	clear();
	allocate(string.size());
	memcpy(getBuffer().get(), string.c_str(), getSize());
}

void pa::FileBuffer::clear()
{
	m_buffer = nullptr;
	m_size = 0;
}

namespace
{
	std::string combinePaths(const std::string& path1, const std::string& path2)
	{
		// <todo> make work with all path types
		std::string result = path1;
		if (!result.empty() && result[result.size() - 1] != '/')
		{
			result += '/';
		}
		result += path2;
		return result;
	}

	std::string makeFilePath(const pa::FileSystem& fileSystem, pa::FileStorage storage, const std::string& path)
	{
		// <todo> add directory separators when building paths
		switch (storage)
		{
		case pa::FileStorage::EngineAsset: return combinePaths(fileSystem.getSettings().engineAssetPath, path);
		case pa::FileStorage::UserAsset: return combinePaths(fileSystem.getSettings().userAssetPath, path);
		case pa::FileStorage::Internal: return combinePaths(fileSystem.getSettings().internalPath, path);
		default:
			PA_ASSERTF(false, "Unknown FileStorage value");
			return "";
		}
	}
}

pa::FilePath::FilePath(const pa::FileSystem& fileSystem, pa::FileStorage storage, const std::string& path)
	: m_fileSystem(fileSystem)
	, m_path(makeFilePath(fileSystem, storage, path))
	, m_storage(storage)
{
}

const std::string& pa::FilePath::asString() const
{
	return m_path;
}

pa::FileResult pa::FilePath::read(FileBuffer& buffer) const
{
	return m_fileSystem.read(*this, buffer);
}

pa::FileResult pa::FilePath::write(const FileBuffer& buffer) const
{
	return m_fileSystem.write(*this, buffer);
}

pa::FileResult pa::FilePath::getModificationTime(std::chrono::system_clock::time_point& modificationTime) const
{
	return m_fileSystem.getModificationTime(*this, modificationTime);
}

pa::FileStorage pa::FilePath::getStorage() const
{
	return m_storage;
}

pa::FileSystem::FileSystem(pa::PlatformSettings::FileSystem settings)
	: m_settings(settings)
{
}

/*static*/ const char* pa::FileSystem::getResultString(pa::FileResult result)
{
	switch (result)
	{
	case pa::FileResult::Success: return "Success";
	case pa::FileResult::NotFound: return "File not found";
	case pa::FileResult::ReadError: return "File read error";
	case pa::FileResult::IOError: return "File I/O error";
	case pa::FileResult::AccessDenied: return "Access denied";
	case pa::FileResult::NameTooLong: return "File name too long";
	case pa::FileResult::WriteError: return "File write error";
	default:
		PA_ASSERTF(false, "Result string not implemented");
		return "";
	}
}

const pa::PlatformSettings::FileSystem& pa::FileSystem::getSettings() const
{
	return m_settings;
}

pa::FileResult pa::FileSystem::read(const pa::FilePath& path, pa::FileBuffer& buffer) const
{
	FILE* file;
	{
		auto result = openFile(&file, path.asString().c_str(), "rb");
		if (result != pa::FileResult::Success)
		{
			// Cannot open the file so return error code
			return result;
		}
	}

	// Obtain the file size
	fseek(file, 0, SEEK_END);
	auto length = ftell(file);
	rewind(file);
	buffer.allocate(length);

	// Copy the file into the buffer
	pa::FileResult result = pa::FileResult::Success;
	auto readLength = fread(buffer.getBuffer().get(), sizeof(unsigned char), length, file);
	if (readLength != length)
	{
		result = pa::FileResult::ReadError;
	}

	fclose(file);
	return result;
}

pa::FileResult pa::FileSystem::write(const pa::FilePath& path, const pa::FileBuffer& buffer) const
{
	static std::mutex writeMutex;
	std::lock_guard<std::mutex> lock(writeMutex);
	std::string temporaryPath = path.asString() + ".tmp";
	FILE* file = nullptr;
	for (unsigned int suffix = 0; ; ++suffix)
	{
		const auto openResult = openFile(&file, temporaryPath.c_str(), "wbx");
		if (openResult == FileResult::Success)
		{
			break;
		}
		if (errno != EEXIST)
		{
			pa::Log::info("Failed to create temporary file {}: errno {}", temporaryPath, errno);
			return openResult;
		}
		// Never truncate a pre-existing sibling or another writer's temporary file.
		temporaryPath = path.asString() + ".tmp." + std::to_string(suffix);
	}

	bool success = buffer.getSize() == 0 ||
		fwrite(buffer.getBuffer().get(), 1, buffer.getSize(), file) == buffer.getSize();
	if (fflush(file) != 0)
	{
		success = false;
	}
#ifdef _WIN32
	if (_commit(_fileno(file)) != 0)
#else
	if (fsync(fileno(file)) != 0)
#endif
	{
		success = false;
	}
	if (fclose(file) != 0)
	{
		success = false;
	}
	if (success)
	{
#ifdef _WIN32
		DWORD error = ERROR_SUCCESS;
		for (unsigned int attempt = 0; attempt < 7; ++attempt)
		{
			success = MoveFileExA(temporaryPath.c_str(), path.asString().c_str(),
				MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
			error = success ? ERROR_SUCCESS : GetLastError();
			if (success || (error != ERROR_ACCESS_DENIED && error != ERROR_SHARING_VIOLATION) || attempt == 6)
			{
				break;
			}
			// Windows scanners can briefly hold a just-closed file without delete sharing.
			Sleep(1u << attempt);
		}
		if (!success)
		{
			pa::Log::info("Failed to replace {}: Windows error {}", path.asString(), error);
		}
#else
		success = std::rename(temporaryPath.c_str(), path.asString().c_str()) == 0;
		if (!success)
		{
			pa::Log::info("Failed to replace {}: errno {}", path.asString(), errno);
		}
#endif
	}
	if (!success)
	{
		if (std::remove(temporaryPath.c_str()) != 0)
		{
			pa::Log::info("Failed to remove temporary file: {}", temporaryPath);
		}
		return FileResult::WriteError;
	}
	return FileResult::Success;
}

pa::FileResult pa::FileSystem::getModificationTime(const pa::FilePath& path, std::chrono::system_clock::time_point& modificationTime) const
{
	struct stat st;
	int ret = stat(path.asString().c_str(), &st);

	if (ret == -1)
	{
		return pa::FileResult::ReadError;
	}
	else
	{
		modificationTime = std::chrono::system_clock::from_time_t(st.st_mtime);
		return pa::FileResult::Success;
	}
}