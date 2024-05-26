//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef CLIP_DATA_H
#define CLIP_DATA_H

#include "ProtoVersion.h"
#include "FrameBucketEntry.h"
#include "ClipData.pb.h"

namespace Azul
{
	class ClipData
	{
	public:
		ClipData();
		ClipData(const ClipData &) = delete;
		ClipData &operator = (const ClipData &) = delete;
		~ClipData();

		ClipData(unsigned int _numKeyFrames, unsigned int _numBones);

		// Serialization 
		void Serialize(ClipData_proto &out) const;
		void Deserialize(const ClipData_proto &in);

		void Print(const char *const pName) const;

	public:
		char              pVersion[protoVersion::VERSION_NUM_BYTES];
		unsigned int      numKeyFrames;
		unsigned int      numBones;
		FrameBucketEntry *poFrameBucketEntry;
	};

}

#endif

// --- End of File ---
