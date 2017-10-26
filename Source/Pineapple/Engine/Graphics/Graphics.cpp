/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/Map.h>
#include <Pineapple/Engine/Graphics/Sprite.h>

pa::Graphics::Graphics(const pa::Vect2<int>& size)
	: m_size(size)
	, m_settingSize(size)
{
}

pa::Graphics::~Graphics()
{
}

void pa::Graphics::resize(pa::Graphics::ResizeMode mode, const pa::Vect2<int>& platformSize)
{
	const pa::Vect2<float> p = platformSize;
	const pa::Vect2<float> u = m_settingSize;

	pa::Vect2<float> projectionSize;
	pa::Vect2<float> projectionPosition;

	if (ResizeMode::Fill == mode || ResizeMode::Fit == mode)
	{
		pa::Log::info("Resizing keeping aspect ratio: {} * {} -> {} * {}", (int)u.x, (int)u.y, (int)p.x, (int)p.y);

		float platformRatio = p.y / p.x;
		float graphicsRatio = u.y / u.x;

		if (ResizeMode::Fill == mode)
		{
			if (platformRatio > graphicsRatio)
			{
				projectionSize.x = (graphicsRatio / platformRatio) * u.x;
				projectionSize.y = u.y;
				projectionPosition.x = (u.x - projectionSize.x) / 2;
				projectionPosition.y = 0;
			}
			else
			{
				projectionSize.x = u.x;
				projectionSize.y = (platformRatio / graphicsRatio) * u.y;
				projectionPosition.x = 0;
				projectionPosition.y = (u.y - projectionSize.y) / 2;
			}

			setViewport(0, 0, (int)p.x, (int)p.y);
		}
		else
		{
			pa::Vect2<float> viewportPos;

			projectionPosition.cart(0, 0);
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
		projectionPosition.cart(0, 0);
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
