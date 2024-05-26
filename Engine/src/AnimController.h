//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "AnimTime.h"
#include "DLink.h"

namespace Azul
{
	class Anim;
	class TimerController;

	class AnimController: public DLink
	{
	public:
		AnimController(Anim *pAnim, AnimTime delta);
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void Update();

		virtual bool Compare(DLink* pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

	private:
		TimerController *poTimerControl;
		Anim *poAnim;
	};
}

#endif

// --- End of File ---
