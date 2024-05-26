//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FrameBucket.h"
#include "ComputeRSVBuffer.h"
  
namespace Azul
{
	FrameBucket::FrameBucket()
		: nextBucket{nullptr},
		prevBucket{nullptr},
		KeyTime{AnimTime(AnimTime::Duration::ZERO)},
		poBoneRSV{nullptr}
	{

	}

	FrameBucket::~FrameBucket()
	{
		delete this->poBoneRSV;
		this->poBoneRSV = nullptr;
	}
}

// --- End of File ---
