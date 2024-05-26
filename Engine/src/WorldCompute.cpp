//----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "WorldCompute.h"
#include "File.h"
#include "HierarchyMan.h"
#include "HierarchyData.h"
#include "MathEngine.h"
#include "Mixer.h"
#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "ComputeCBVBuffer.h"
#include "InvBindMan.h"

namespace Azul
{

	WorldCompute::WorldCompute(Mixer *pMixer, Hierarchy::Name hierarchyName, InvBind::Name invBindName)
		: pMixerABIn{nullptr},
		poHierarchyTable{nullptr},
		poUAVWorldMat{nullptr},
		poConstBuffer{nullptr},
		poWorldConstant{nullptr},
		boneCount{0},
		hierarchyDepth{0},
		poVsBoneWorld{nullptr},
		poVsInvBind{nullptr}
	{
		assert(pMixer);
		assert(pMixer->poMixerABOut);
		this->pMixerABIn = pMixer->poMixerABOut;

		Hierarchy *pHierarchy = HierarchyMan::Find(hierarchyName);
		this->hierarchyDepth = pHierarchy->depth;
		this->boneCount = pHierarchy->numBones;
	

		this->poHierarchyTable = new ComputeRSVBuffer(this->hierarchyDepth * this->boneCount, sizeof(int));
		assert(poHierarchyTable);
		this->poHierarchyTable->Transfer(pHierarchy->poTableArray);

		this->poUAVWorldMat = new ComputeUAVBuffer(this->boneCount, sizeof(Mat4));
		assert(this->poUAVWorldMat);

		this->poVsBoneWorld = new ComputeRSVBuffer(this->boneCount, sizeof(Mat4));
		assert(this->poVsBoneWorld);

		this->poVsInvBind = new ComputeRSVBuffer(this->boneCount, sizeof(Mat4));
		assert(this->poVsInvBind);

		this->poConstBuffer = new ComputeCBVBuffer(sizeof(WorldConstant));
		assert(this->poConstBuffer);

		this->poWorldConstant = new WorldConstant();
		assert(this->poWorldConstant);

		// load the inverse bind once
		this->privLoadInvBind(invBindName);

	}

	WorldCompute::~WorldCompute()
	{
		delete this->poHierarchyTable;
		this->poHierarchyTable = nullptr;

		delete this->poUAVWorldMat;
		this->poUAVWorldMat = nullptr;

		delete this->poVsBoneWorld;
		this->poVsBoneWorld = nullptr;

		delete this->poVsInvBind;
		this->poVsInvBind = nullptr;

		delete this->poConstBuffer;
		this->poConstBuffer = nullptr;

		delete this->poWorldConstant;
		this->poWorldConstant = nullptr;
	}


	void * WorldCompute::GetConstBuff() const
	{
		this->poWorldConstant->hierarchyDepth = this->hierarchyDepth;
		this->poWorldConstant->numBones = this->boneCount;

		return this->poWorldConstant;
	}

	void WorldCompute::privLoadInvBind(InvBind::Name name)
	{
		InvBind *pInvBind = InvBindMan::Find(name);

		this->poVsInvBind->Transfer(pInvBind->poInvBindArray);
	}

}

// --- End of File ---
