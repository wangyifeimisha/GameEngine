//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef SKEL_DATA_H
#define SKEL_DATA_H

#include "ProtoVersion.h"
#include "SkelData.pb.h"
#include "SkelEntry.h"

namespace Azul
{
	class SkelData
	{
	public:
		SkelData();
		SkelData(const SkelData &) = delete;
		SkelData &operator = (const SkelData &) = delete;
		~SkelData();

		SkelData(unsigned int _numBones);

		// Serialization 
		void Serialize(SkelData_proto &out) const;
		void Deserialize(const SkelData_proto &in);

		void Print(const char *const pName) const;

	public:
		char           pVersion[protoVersion::VERSION_NUM_BYTES];
		unsigned int   numBones;
		SkelEntry     *poSkelEntry;
	};

}

#endif

// --- End of File ---
