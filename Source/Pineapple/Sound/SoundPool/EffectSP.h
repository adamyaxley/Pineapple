#pragma once

#include <Pineapple/Engine/Sound/Effect.h>
#include <Pineapple/Sound/SoundPool/BindingEffectSP.h>

namespace pa
{
	class EffectSP : public Effect
	{
	public:

		EffectSP(const FilePath& path, const BindingEffectSP& binding);
		~EffectSP();

		virtual bool onLoad() override;
		virtual bool onUnload() override;

		virtual void play() override;
		virtual void loop() override;

	private:

		const BindingEffectSP& m_binding;

		int m_soundId;
	};
}