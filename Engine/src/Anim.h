//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"

namespace Azul
{
	class Clip;
	class Mixer;

	class Anim
	{
	public:
		Anim(Clip *pClip, Mixer *pMixer);

		Anim() = delete;
		Anim(const Anim &) = delete;
		Anim &operator = (const Anim &) = delete;
		~Anim();

		void Animate(AnimTime tCurr);
		AnimTime FindMaxTime();

	private:
		Clip *pClip;
		Mixer *pMixer;
	};

}

#endif

// --- End of File ---