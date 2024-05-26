//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MIXER_H
#define MIXER_H

namespace Azul
{
	class Clip;
	class ComputeRSVBuffer;
	class ComputeUAVBuffer;
	class ComputeCBVBuffer;

	// structure for Constant Compute buffer needs to be multiple of 16 bytes
	struct MixerConstant
	{
		float ts;
		unsigned int numBones;
		int pad0;
		int pad1;
	};

	class Mixer
	{
	public:
		Mixer(Clip *pClip);

		Mixer() = delete;
		Mixer(const Mixer &) = delete;
		Mixer &operator = (const Mixer &) = delete;
		virtual ~Mixer();

		void *GetConstBuff() const;

	public:
		ComputeRSVBuffer   *pKeyA;
		ComputeRSVBuffer   *pKeyB;
		ComputeUAVBuffer   *poMixerABOut;	
		ComputeCBVBuffer   *poConstBuffer;
		MixerConstant      *poMixerConstant;
		float              tS;
		int                numBones;
	};
}

#endif

// --- End of File ---
