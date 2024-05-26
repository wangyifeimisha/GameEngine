//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef FRAME_BUCKET_ENTRY_H
#define FRAME_BUCKET_ENTRY_H

#include "BoneEntry.h"

#include "FrameBucketEntry.pb.h"

namespace Azul
{
	class FrameBucketEntry
	{
	public:
		FrameBucketEntry();
		FrameBucketEntry(const FrameBucketEntry &) = delete;
		FrameBucketEntry &operator = (const FrameBucketEntry &);
		~FrameBucketEntry();

		FrameBucketEntry(unsigned int _numBones);

		// Serialization 
		void Serialize(FrameBucketEntry_proto &out) const;
		void Deserialize(const FrameBucketEntry_proto &in);

		void Print(const char *const pName) const;

	public:
		unsigned int  keyFrame;
		unsigned int  numBones;
		float         keyTime;
		int           keyTimeIndex;
		BoneEntry *poBoneEntry;
	};

}

#endif

// --- End of File ---
