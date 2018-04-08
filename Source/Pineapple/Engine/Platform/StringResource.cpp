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
	m_data = buffer.createString();
	pa::Log::info("Loaded String Resource: {}", getPath().asString());
	return true;
}

bool pa::StringResource::onUnload()
{
	m_data.clear();
	m_data.shrink_to_fit();
	return true;
}

const std::string& pa::StringResource::getData() const
{
	return m_data;
}