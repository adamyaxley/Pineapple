/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/Map.h>
#include <Pineapple/Engine/Graphics/Sprite.h>

pa::Graphics::Graphics(const pa::PlatformSettings::Graphics& settings, const pa::FileSystem& fileSystem)
	: m_size(settings.size)
	, m_settings(settings)
	, m_fileSystem(fileSystem)
{
}

pa::Graphics::~Graphics()
{
}

void pa::Graphics::resize(pa::Graphics::ResizeMode mode, const pa::Vect2<int>& platformSize)
{
	const pa::Vect2<float> p = platformSize;
	const pa::Vect2<float> u = m_settings.size;

	const bool isFillMode = ResizeMode::FillCenter == mode || ResizeMode::FillMin == mode || ResizeMode::FillMax == mode;

	pa::Vect2<float> projectionSize;
	pa::Vect2<float> projectionPosition;

	if (isFillMode || ResizeMode::Fit == mode)
	{
		pa::Log::info("Resizing keeping aspect ratio: {} * {} -> {} * {}", (int)u.x, (int)u.y, (int)p.x, (int)p.y);

		float platformRatio = p.y / p.x;
		float graphicsRatio = u.y / u.x;

		if (isFillMode)
		{
			if (platformRatio > graphicsRatio)
			{
				projectionSize.x = (graphicsRatio / platformRatio) * u.x;
				projectionSize.y = u.y;
				projectionPosition.y = 0;

				switch (mode)
				{
				case ResizeMode::FillCenter:
					projectionPosition.x = (u.x - projectionSize.x) / 2;
					break;
				case ResizeMode::FillMin:
					projectionPosition.x = 0;
					break;
				case ResizeMode::FillMax:
					projectionPosition.x = u.x - projectionSize.x;
					break;
				}
			}
			else
			{
				projectionSize.x = u.x;
				projectionSize.y = (platformRatio / graphicsRatio) * u.y;
				projectionPosition.x = 0;

				switch (mode)
				{
				case ResizeMode::FillCenter:
					projectionPosition.y = (u.y - projectionSize.y) / 2;
					break;
				case ResizeMode::FillMin:
					projectionPosition.y = 0;
					break;
				case ResizeMode::FillMax:
					projectionPosition.y = u.y - projectionSize.y;
					break;
				}
			}

			setViewport(0, 0, (int)p.x, (int)p.y);
		}
		else
		{
			pa::Vect2<float> viewportPos;

			projectionPosition.set(0, 0);
			projectionSize = u;

			// Fit - resize so that the whole view fits in the screen, while keeping the aspect ratio
			if (platformRatio > graphicsRatio)
			{
				viewportPos.x = 0;
				viewportPos.y = (p.y - (graphicsRatio / platformRatio) * p.y) / 2;
			}
			else
			{
				viewportPos.x = (p.x - (platformRatio / graphicsRatio) * p.x) / 2;
				viewportPos.y = 0;
			}

			setViewport((int)viewportPos.x, (int)viewportPos.y, (int)p.x - 2 * (int)viewportPos.x,
						(int)p.y - 2 * (int)viewportPos.y);
		}
	}
	else if (ResizeMode::Stretch == mode)
	{
		projectionSize = u;
		projectionPosition.set(0, 0);
		setViewport(0, 0, (int)p.x, (int)p.y);
	}
	else
	{
		PA_ASSERTF(false, "Unknown ResizeMode: {}", static_cast<int>(mode));
	}

	pa::Log::info("Resizing to: {} * {}", (int)projectionSize.x, (int)projectionSize.y);

	setProjection((int)projectionPosition.x, (int)projectionPosition.y,
				  (int)projectionPosition.x + (int)projectionSize.x, (int)projectionPosition.y + (int)projectionSize.y);
}

void pa::Graphics::setProjection(int x, int y, int x2, int y2)
{
	m_projectionPosition.x = x;
	m_projectionPosition.y = y;
	m_size.x = x2;
	m_size.y = y2;
}

std::unique_ptr<pa::Sprite> pa::Graphics::createSprite(std::vector<std::shared_ptr<pa::Texture>>& frames)
{
	return std::make_unique<pa::Sprite>(m_renderSystem, frames, 0);
}
