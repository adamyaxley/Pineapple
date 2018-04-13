#pragma once

#include <Pineapple/Engine/Container/Vect2.h>
#include <string>
#include <memory>

namespace pa
{
	struct PlatformSettings
	{
		PlatformSettings();

		std::string title{ "Pineapple Application" };

		struct FileSystem
		{
			std::string engineAssetPath{ "Assets" };
			std::string userAssetPath{ "Assets" };
			std::string internalPath{ "Internal" };
		} fileSystem;

		struct Graphics
		{
			bool use = true;
			Vect2<int> size;
			float zoom;
		} graphics;

		struct Sound
		{
			bool use = true;
		} sound;

		bool loadFromFile(const char* filename = "pineapple.json");

		void print() const;
	};
}