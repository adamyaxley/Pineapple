#pragma once

#include <Pineapple/Engine/Platform/Resource.h>

namespace pa
{
	class StringResource : public Resource
	{
	public:

		StringResource(const FilePath& path);
		virtual ~StringResource() {}

		virtual bool onLoad() override;
		virtual bool onUnload() override;
		virtual bool onSave() override;

		std::string& getString();

	private:

		std::string m_string;
	};
}