/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

PA_FORCE_INLINE const pa::Vect2<int>& pa::Graphics::getSize() const
{
	return m_size;
}

PA_FORCE_INLINE const pa::Vect2<int>& pa::Graphics::getProjectionPosition() const
{
	return m_projectionPosition;
}

PA_FORCE_INLINE pa::Vect2<float>& pa::Graphics::getSpriteView()
{
	return m_spriteView;
}

PA_FORCE_INLINE pa::Vect2<float>& pa::Graphics::getMapView()
{
	return m_mapView;
}

PA_FORCE_INLINE pa::Vect2<float>& pa::Graphics::getTextView()
{
	return m_textView;
}

PA_FORCE_INLINE const pa::Vect2<float>& pa::Graphics::getSpriteView() const
{
	return m_spriteView;
}

PA_FORCE_INLINE const pa::Vect2<float>& pa::Graphics::getMapView() const
{
	return m_mapView;
}

PA_FORCE_INLINE const pa::Vect2<float>& pa::Graphics::getTextView() const
{
	return m_textView;
}

PA_FORCE_INLINE pa::ResourceManager& pa::Graphics::getResourceManager()
{
	return m_resourceManager;
}

PA_FORCE_INLINE pa::RenderSystem& pa::Graphics::getRenderSystem()
{
	return m_renderSystem;
}

PA_FORCE_INLINE void pa::Graphics::setDeferredProgram(pa::Program* program)
{
	m_deferredProgram = program;
}

PA_FORCE_INLINE pa::Program* pa::Graphics::getDeferredProgram()
{
	return m_deferredProgram;
}