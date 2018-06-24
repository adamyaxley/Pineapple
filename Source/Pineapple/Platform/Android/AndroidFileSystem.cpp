#include <Pineapple/Platform/Android/AndroidFileSystem.h>
#include <Pineapple/Platform/Android/AndroidBridge.h>
#include <Pineapple/Engine/Platform/Log.h>

std::unique_ptr<pa::FileSystem> pa::MakeInternal::fileSystem(const pa::PlatformSettings::FileSystem& settings)
{
	pa::PlatformSettings::FileSystem androidSettings = settings;

	// Android Assets are loaded without any directory
	androidSettings.userAssetPath.clear();
	androidSettings.engineAssetPath.clear();

	// Set the Android internal data path
	androidSettings.internalPath = pa::AndroidBridge::getInternalDataPath();

	return std::make_unique<pa::AndroidFileSystem>(androidSettings);
}

namespace
{
	pa::FileResult openFile(AAsset** asset, const char* path)
	{
		AAssetManager* assetManager = pa::AndroidBridge::getNativeActivity()->assetManager;
		*asset = AAssetManager_open(assetManager, path, AASSET_MODE_UNKNOWN);

		if (*asset == NULL)
		{
			return pa::FileResult::NotFound;
		}

		return pa::FileResult::Success;
	}
}

pa::AndroidFileSystem::AndroidFileSystem(pa::PlatformSettings::FileSystem settings)
	: pa::FileSystem(settings)
{}

pa::FileResult pa::AndroidFileSystem::read(const pa::FilePath& path, pa::FileBuffer& buffer) const
{
	if (path.getStorage() == pa::FileStorage::Internal)
	{
		return pa::FileSystem::read(path, buffer);
	}
	else
	{
		AAsset* asset;

		auto result = openFile(&asset, path.asString().c_str());
		if (result != pa::FileResult::Success)
		{
			return result;
		}

		off_t size = AAsset_getLength(asset);
		buffer.allocate(size);
		int bytes = AAsset_read(asset, buffer.getBuffer().get(), size);

		if (bytes == 0 || bytes < 0 || bytes != size)
		{
			AAsset_close(asset);
			return pa::FileResult::ReadError;
		}

		AAsset_close(asset);
		return pa::FileResult::Success;
	}
}

pa::FileResult pa::AndroidFileSystem::write(const pa::FilePath& path, const pa::FileBuffer& buffer) const
{
	if (path.getStorage() == pa::FileStorage::Internal)
	{
		return pa::FileSystem::write(path, buffer);
	}
	else
	{
		pa::Log::info("Writing to the Asset folder is not supported on Android ({})", path.asString());
		return pa::FileResult::AccessDenied;
	}
}

pa::FileResult pa::AndroidFileSystem::getModificationTime(const pa::FilePath& path, std::chrono::system_clock::time_point& modificationTime) const
{
	pa::Log::info("FileSystem::getModificationTime is not supported on Android ({})", path.asString());
	return pa::FileResult::AccessDenied;
}