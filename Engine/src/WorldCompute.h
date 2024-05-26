//----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WORLD_COMPUTE_H
#define WORLD_COMPUTE_H

#include "Hierarchy.h"
#include "InvBind.h"

namespace Azul
{
	class Mixer;
	class ComputeRSVBuffer;
	class ComputeUAVBuffer;
	class ComputeCBVBuffer;

	// structure for Constant Compute buffer needs to be multiple of 16 bytes
	struct WorldConstant
	{
		unsigned int hierarchyDepth;
		unsigned int numBones;
		int pad0;
		int pad1;
	};

	class WorldCompute
	{
	public:
		WorldCompute(Mixer *pMixer, Hierarchy::Name hierarchyName, InvBind::Name invBindName);

		WorldCompute() = delete;
		WorldCompute(const WorldCompute &) = delete;
		WorldCompute &operator = (const WorldCompute &) = delete;
		virtual ~WorldCompute();

		void *GetConstBuff() const;

	private:
		void privLoadInvBind(InvBind::Name name);

	public:
		// World compute shader data
		ComputeUAVBuffer *pMixerABIn;
		ComputeRSVBuffer *poHierarchyTable;
		ComputeUAVBuffer *poUAVWorldMat;
		ComputeCBVBuffer *poConstBuffer;
		WorldConstant    *poWorldConstant;
		int    boneCount;
		int    hierarchyDepth;

		// for Skin Vertex shader (can't have a UAV only a RSV)
		ComputeRSVBuffer *poVsBoneWorld;  
		ComputeRSVBuffer *poVsInvBind;

	};
}

#endif

// --- End of File ---
