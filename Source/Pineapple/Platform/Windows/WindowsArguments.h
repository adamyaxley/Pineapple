/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace pa
{
	class WindowsArguments : public Arguments
	{
	public:
		WindowsArguments(HINSTANCE hInstance, int nCmdShow)
			: m_hInstance(hInstance)
			, m_nCmdShow(nCmdShow)
		{
		}

		HINSTANCE getInstance() const
		{
			return m_hInstance;
		}

		int getCmdShow() const
		{
			return m_nCmdShow;
		}

	private:
		const HINSTANCE m_hInstance;
		const int m_nCmdShow;
	};
}
