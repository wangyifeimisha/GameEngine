//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef SKEL_ENTRY_H
#define SKEL_ENTRY_H

#include "SkelEntry.pb.h"

namespace Azul
{

	class SkelEntry
	{
	public:
		static const unsigned int SKELETON_NAME_SIZE = 64;

	public:
		SkelEntry();
		SkelEntry(const SkelEntry &) = delete;
		SkelEntry &operator = (const SkelEntry &) = delete;
		~SkelEntry();

		void set(int _nodeIndex,
					int   _parentIndex,
					char  *pNodeName);

		// Serialization 
		void Serialize(SkelEntry_proto &out) const;
		void Deserialize(const SkelEntry_proto &in);

		void Print(const char *const pName) const;

	public:
		int   nodeIndex;
		int   parentIndex;
		char  pNodeName[SKELETON_NAME_SIZE];

	};

}

#endif

// --- End of File ---
