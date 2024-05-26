//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SKELETON_H
#define SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"
#include "Skel.h"
#include "Clip.h"
#include "ComputeUAVBuffer.h"

namespace Azul
{
	class Skeleton
	{
	public:

		Skeleton(Clip *pClip, ComputeUAVBuffer *pBone);

		Skeleton() = delete;
		Skeleton(const Skeleton &) = delete;
		Skeleton &operator = (const Skeleton &) = delete;
		~Skeleton();

		GameObjectAnim *GetFirstBone();
		GameObjectAnim *FindBoneByIndex(int index);
		int GetNumBones() const;

	private:
		void privSetAnimationHierarchy(ComputeUAVBuffer *pBoneResult, Skel::Name skelName);

	private:
		GameObjectAnim *pFirstBone;
		int             numBones;
	};
}

#endif

// --- End of File ---
