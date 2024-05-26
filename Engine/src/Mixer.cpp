//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mixer.h"
#include "MathApp.h"
#include "ShaderObjectNodeMan.h"
#include "ComputeCBVBuffer.h"
#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "DirectXDeviceMan.h"
#include "Bone.h"
#include "Clip.h"

namespace Azul
{
	Mixer::Mixer(Clip *pClip)
		:pKeyA{nullptr},
		pKeyB{nullptr},
		poMixerABOut{nullptr},
		poConstBuffer{nullptr},
		poMixerConstant{nullptr},
		tS{0},
		numBones{0}
	{
		assert(pClip);

		this->numBones = pClip->GetNumBones();
		this->poMixerABOut = new ComputeUAVBuffer(this->numBones, sizeof(Bone));
		assert(this->poMixerABOut);

		this->poConstBuffer = new ComputeCBVBuffer(sizeof(MixerConstant));
		assert(this->poConstBuffer);

		this->poMixerConstant = new MixerConstant();
		assert(poMixerConstant);
	}

	Mixer::~Mixer()
	{
		delete this->poMixerABOut;
		this->poMixerABOut = nullptr;

		delete this->poConstBuffer;
		this->poConstBuffer = nullptr;

		delete this->poMixerConstant;
		this->poMixerConstant = nullptr;
	}

	void *Mixer::GetConstBuff() const
	{
		this->poMixerConstant->numBones = this->numBones;
		this->poMixerConstant->ts = this->tS;

		return this->poMixerConstant;
	}

}

// --- End of File ---
