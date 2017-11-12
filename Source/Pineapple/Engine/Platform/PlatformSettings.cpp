#include <Pineapple/Engine/Platform/FileSystem.h>
#include <Pineapple/Engine/Platform/PlatformSettings.h>
#include <Pineapple/Engine/Platform/Log.h>
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>

pa::PlatformSettings::PlatformSettings()
{
	loadFromFile();
}

bool pa::PlatformSettings::loadFromFile(const char* filename /* = pineapple.json */)
{
	std::string contents;
	{
		// Create a temporary file system
		pa::PlatformSettings::FileSystem fileSystemSettings;
		fileSystemSettings.internalPath = "";
		auto tempFileSystem = pa::MakeInternal::fileSystem(fileSystemSettings);
		
		pa::FilePath path(*tempFileSystem.get(), pa::FileStorage::Internal, filename);
		pa::FileBuffer buffer;
		auto result = path.read(buffer);

		if (result != pa::FileResult::Success)
		{
			pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), filename);
			return false;
		}
		contents = buffer.createString();
	}

	// Load json
	rapidjson::Document document;
	document.Parse<0>(contents.c_str());

	if (document.HasParseError())
	{
		pa::Log::info("Failed to parse platform settings file {}, error was: {}", filename, document.GetParseError());
		return false;
	}

	if (document.IsObject())
	{
		if (document.HasMember("engineAssetPath"))
		{
			auto& object = document["engineAssetPath"];

			if (object.IsString())
			{
				fileSystem.engineAssetPath = object.GetString();
			}
			else
			{
				pa::Log::info("Could not parse engineAssetPath");
			}
		}
		if (document.HasMember("userAssetPath"))
		{
			auto& object = document["userAssetPath"];

			if (object.IsString())
			{
				fileSystem.userAssetPath = object.GetString();
			}
			else
			{
				pa::Log::info("Could not parse userAssetPath");
			}
		}
	}

	pa::Log::info("Loaded settings from {}", filename);
	return true;
}

void pa::PlatformSettings::print() const
{
	pa::Log::info("Title: {}", title);
	pa::Log::info("EngineAssetPath: {}", fileSystem.engineAssetPath);
	pa::Log::info("UserAssetPath: {}", fileSystem.userAssetPath);
	pa::Log::info("InternalPath: {}", fileSystem.internalPath);
	pa::Log::info("Graphics: (Size: {}x{})", graphics.size.x, graphics.size.y);
}