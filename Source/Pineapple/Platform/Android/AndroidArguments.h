#pragma once

struct android_app;

namespace pa
{
	class AndroidArguments : public Arguments
	{
	public:
		AndroidArguments(android_app* state)
			: m_state(state)
		{
		}

		android_app* getState()
		{
			return m_state;
		}

	private:
		android_app* m_state;
	};
}
