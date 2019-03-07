#include <Pineapple/Engine/Platform/StringResource.h>
#include <Pineapple/Engine/Platform/Log.h>

pa::StringResource::StringResource(const pa::FilePath& path)
	: pa::Resource(path)
{
}

bool pa::StringResource::onLoad()
{
	pa::FileBuffer buffer;
	auto result = getPath().read(buffer);
	if (result != pa::FileResult::Success)
	{
		pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), getPath().asString());
		return false;
	}
	m_string = buffer.createString();
	pa::Log::info("Loaded String Resource: {}", getPath().asString());
	return true;
}

bool pa::StringResource::onUnload()
{
	m_string.clear();
	m_string.shrink_to_fit();
	return true;
}

bool pa::StringResource::onSave()
{
	pa::FileBuffer buffer;
	buffer.copyFromString(m_string);
	auto result = getPath().write(buffer);
	if (result != pa::FileResult::Success)
	{
		pa::Log::info("{}: {}", pa::FileSystem::getResultString(result), getPath().asString());
		return false;
	}

	return true;
}

std::string& pa::StringResource::getString()
{
	return m_string;
}