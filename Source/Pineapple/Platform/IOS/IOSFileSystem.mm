#include <Pineapple/Engine/Platform/FileSystem.h>
#include <Pineapple/Platform/IOS/IOSBridge.h>

std::unique_ptr<pa::FileSystem> pa::MakeInternal::fileSystem(const pa::PlatformSettings::FileSystem& settings)
{
	pa::PlatformSettings::FileSystem iosSettings = settings;

	// Set the IOS asset path
	iosSettings.userAssetPath = pa::IOSBridge::getAssetPath();
	iosSettings.engineAssetPath = iosSettings.userAssetPath;

	// Set the IOS internal data path
	iosSettings.internalPath = pa::IOSBridge::getInternalPath();

	return std::make_unique<pa::FileSystem>(iosSettings);
}
