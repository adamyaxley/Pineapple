/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename... TRest>
PA_FORCE_INLINE pa::AnimatedSprite::AnimatedSprite(pa::RenderSystem& renderSystem, pa::Texture* texture,
												   TRest&&... textures)
	: pa::AnimatedSprite(renderSystem, false, texture, textures...)
{
}

template <typename... TRest>
PA_FORCE_INLINE pa::AnimatedSprite::AnimatedSprite(pa::RenderSystem& renderSystem, bool recurring, pa::Texture* texture,
												   TRest&&... textures)
	: pa::AnimatedSprite(renderSystem, true, textures...)
{
	m_frameList.push_back(texture->createSprite());

	if (!recurring)
	{
		hideAll();

		m_frameList[m_frame]->setVisible(true);
		setSize(m_frameList[m_frame]->getSize());
		setOrigin(getSize() / 2);
	}
}