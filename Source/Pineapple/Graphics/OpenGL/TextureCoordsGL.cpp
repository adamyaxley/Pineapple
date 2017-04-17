/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Graphics/OpenGL/TextureCoordsGL.h>

pa::TextureCoordsGL::TextureCoordsGL(float x1, float y1, float x2, float y2)
{
	set(x1, y1, x2, y2);
}

void pa::TextureCoordsGL::set(float x1, float y1, float x2, float y2)
{
	m_value[0] = x1;
	m_value[1] = y2;
	m_value[2] = x2;
	m_value[3] = y2;
	m_value[4] = x1;
	m_value[5] = y1;
	m_value[6] = x2;
	m_value[7] = y1;

	m_valueHFlip[0] = x2;
	m_valueHFlip[1] = y2;
	m_valueHFlip[2] = x1;
	m_valueHFlip[3] = y2;
	m_valueHFlip[4] = x2;
	m_valueHFlip[5] = y1;
	m_valueHFlip[6] = x1;
	m_valueHFlip[7] = y1;
}

pa::TextureCoordsGL::~TextureCoordsGL()
{
}

const GLfloat* pa::TextureCoordsGL::getPointer(bool hFlip, bool vFlip) const
{
	if (hFlip && vFlip)
	{
		PA_ASSERTF(false, "Not implemented yet");
		return m_valueHVFlip;
	}
	else if (hFlip)
	{
		return m_valueHFlip;
	}
	else if (vFlip)
	{
		PA_ASSERTF(false, "Not implemented yet");
		return m_valueVFlip;
	}
	else
	{
		return m_value;
	}
}
