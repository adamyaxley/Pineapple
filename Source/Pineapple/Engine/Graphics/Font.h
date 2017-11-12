/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#include <Pineapple/Engine/Graphics/Text.h>
#include <Pineapple/Engine/Platform/Resource.h>
#include <memory>

namespace pa
{
	class Font : public Resource
	{
	public:
		Font(const FilePath& path);
		~Font();

		virtual std::unique_ptr<Text> createText() = 0;

		virtual void setSize(unsigned int size) = 0;
		virtual unsigned int getSize() = 0;

	private:
	};
}
