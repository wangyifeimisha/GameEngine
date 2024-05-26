//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Clip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

#include "FrameBucket.h"
#include "FrameBucketEntry.h"
#include "ComputeRSVBuffer.h"
#include "StringThis.h"

namespace Azul
{
	Clip::Clip()
		: DLink(),
		mName(Clip::Name::Not_Initialized),
		numBones(0),
		numFrames(0),
		skelName(Skel::Name::Not_Initialized),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr)
	{

	}

	Clip::~Clip()
	{
		delete[] this->poHead;
		this->poHead = nullptr;
	}

	size_t Clip::GetNumBones()
	{
		return this->numBones;
	}

	Skel::Name Clip::GetSkelName()
	{
		return this->skelName;
	}

	void Clip::SetClipName(Name clipName)
	{
		this->mName = clipName;
	}

	bool Clip::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Clip *pDataB = (Clip *)pTarget;

		bool status = false;

		if(this->mName == pDataB->mName)
		{
			status = true;
		}

		return status;
	}

	void Clip::Dump()
	{
		Trace::out("      Clip(%p)\n", this);
		Trace::out("      Name: %s \n", StringMe(this->mName));

		DLink::Dump();
	}

	void Clip::Wash()
	{
		this->mName = Clip::Name::Not_Initialized;
		this->numBones = 0;
		this->numFrames = 0;
		this->skelName = Skel::Name::Not_Initialized;
		this->TotalTime = AnimTime(AnimTime::Duration::ZERO);
		this->poHead = nullptr;
	}

	void Clip::AnimateBones(AnimTime tCurr, Mixer *pMixer)
	{
		assert(pMixer);

		// First one 
		FrameBucket *pTmp = this->poHead;
		int count = 0;

		if(pTmp->nextBucket != nullptr)
		{
			// Find which key frames
			while(tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
			{
				pTmp = pTmp->nextBucket;
				count++;
			}

			// pTmp is the "B" key frame
			// pTmp->prev is the "A" key frame
			FrameBucket *pA = pTmp->prevBucket;
			FrameBucket *pB = pTmp;

			pMixer->pKeyA = pA->poBoneRSV;
			pMixer->pKeyB = pB->poBoneRSV;

			// find the "S" of the time
			pMixer->tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

			//Trace::out("tS: %f  c:%d\n", pMixer->tS,count-1);
		}
		else
		{
			pMixer->pKeyA = pTmp->poBoneRSV;
			pMixer->pKeyB = pTmp->poBoneRSV;

			// find the "S" of the time
			pMixer->tS = 0.0f;
		}
	}

	void Clip::Set(Clip::Name _clipName,
				   unsigned int _numBones,
				   unsigned int _numKeyFrames,
				   FrameBucketEntry *pFrameBucketEntry,
				   Skel::Name _skelName)
	{
		this->mName = _clipName;
		this->numBones = _numBones;
		this->numFrames = _numKeyFrames;
		this->skelName = _skelName;

		// create the array of FrameBuckets
		this->poHead = new FrameBucket[this->numFrames]();

		FrameBucket *pFirstFrame = this->poHead;
		FrameBucket *pCurrFrame = pFirstFrame;
		FrameBucket *pLastFrame = this->poHead + this->numFrames - 1;

		// now add Bones with data in each bucket
		for(size_t i = 0; i < (size_t)this->numFrames; i++)
		{
			// Fix pointers... TODO - make array base completely
			pCurrFrame->nextBucket = (pCurrFrame + 1);
			pCurrFrame->prevBucket = (pCurrFrame - 1);
			pCurrFrame++;

			// ------------------------------------------
			// Transfer Bone data to RSB Buffer
			// ------------------------------------------

			{
				// make the storage - now its a RSV before it was a BoneArray on CPU
				poHead[i].poBoneRSV = new ComputeRSVBuffer(this->numBones, sizeof(Bone));

				// Now fill it

				// Temp CPU buffer
				Bone *pCPUBone = new Bone[this->numBones]();

				// Fill it
				Bone *pTmp = &pCPUBone[0];
				BoneEntry *pEntry = pFrameBucketEntry[i].poBoneEntry;

				for(size_t j = 0; j < this->numBones; j++)
				{
					pTmp[j].S.set(pEntry[j].S.x, pEntry[j].S.y, pEntry[j].S.z);
					pTmp[j].Q.set(pEntry[j].Q.qx, pEntry[j].Q.qy, pEntry[j].Q.qz, pEntry[j].Q.qw);
					pTmp[j].T.set(pEntry[j].T.x, pEntry[j].T.y, pEntry[j].T.z);
				}

				// pBone is filled so transfer it
				poHead[i].poBoneRSV->Transfer(pCPUBone);

				// Remove tmp buffer
				delete[] pCPUBone;
				pCPUBone = nullptr;
			}


			// Create Bones - old
			{
				//poHead[i].poBone = new Bone[this->numBones]();

				//// Fill the Bones
				//Bone *pBone = poHead[i].poBone;
				//BoneEntry *pEntry = pFrameBucketEntry[i].poBoneEntry;

				//// This is replaced with ShaderResource
				//for(size_t j = 0; j < (size_t)this->numBones; j++)
				//{
				//	pBone[j].S.set(pEntry[j].S.x,  pEntry[j].S.y,  pEntry[j].S.z);
				//	pBone[j].Q.set(pEntry[j].Q.qx, pEntry[j].Q.qy, pEntry[j].Q.qz, pEntry[j].Q.qw);
				//	pBone[j].T.set(pEntry[j].T.x,  pEntry[j].T.y,  pEntry[j].T.z);
				//}
			}

			// Critical - keep time in AnimTime
			poHead[i].KeyTime = pFrameBucketEntry[i].keyTimeIndex * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		}

		// fix up the first and last node
		pLastFrame->nextBucket = nullptr;
		pFirstFrame->prevBucket = nullptr;

		this->TotalTime = this->privFindMaxTime();
	}

	int Clip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket *pTmp = this->poHead;

		while(pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket *pTmp = this->poHead;

		while(pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}

}

// --- End of File ---
