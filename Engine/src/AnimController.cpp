//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "TimerController.h"
#include "Anim.h"


namespace Azul
{
	AnimController::AnimController(Anim *pAnim, AnimTime delta)
	{
		// Animation object
		this->poAnim = pAnim;
		assert(this->poAnim);

		// TimerController
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->poTimerControl);

	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete poTimerControl;
	}

	void AnimController::Update()
	{
		this->poTimerControl->Update();

		// interpolate all bones
		this->poAnim->Animate(this->poTimerControl->GetCurrTime());

	}

	bool AnimController::Compare(DLink* pTarget)
	{
		//// This is used in ManBase.Find() 
		assert(pTarget != nullptr);
		//
		//AnimController* pDataB = (AnimController*)pTarget;
		//
		//bool status = false;
		//
		//if (this->mName == pDataB->mName)
		//{
		//	status = true;
		//}
		//
		return true;
	}

	void AnimController::Dump()
	{
		Trace::out("      AnimController(%p)\n", this);
		//Trace::out("      Name: %s \n", StringMe(this->mName));

		//DLink::Dump();
	}

	void AnimController::Wash()
	{
		//this->mName = AnimController::Name::Not_Initialized;
		//this->numBones = 0;
		//// just in case
		//delete[] this->poTableArray;
		//this->poTableArray = nullptr;
	}
}

// --- End of File ---
