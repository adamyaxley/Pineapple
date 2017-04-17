/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

namespace pa
{
	class Counter
	{
	public:
		Counter()
			: m_value(s_nextValue++)
		{
		}

		inline unsigned int getValue() const noexcept
		{
			return m_value;
		}

	private:
		const unsigned int m_value;
		static unsigned int s_nextValue;
	};
}
