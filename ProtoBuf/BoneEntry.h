//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef BONE_ENTRY_H
#define BONE_ENTRY_H

#include "MathEngine.h"
#include "BoneEntry.pb.h"

#include "QuatData.h"
#include "Vec3Data.h"

namespace Azul
{

	class BoneEntry
	{
	public:
		BoneEntry();
		BoneEntry(const BoneEntry &) = delete;
		BoneEntry &operator = (const BoneEntry &) = default;
		~BoneEntry();

		BoneEntry(Vec3 &s, Quat &q, Vec3 &t);
		void set(Vec3 &s, Quat &q, Vec3 &t);

		// Serialization 
		void Serialize(BoneEntry_proto &out) const;
		void Deserialize(const BoneEntry_proto &in);

		void Print(const char *const pName) const;

	public:
		Vec3Data S;
		QuatData Q;
		Vec3Data T;
	};

}

#endif

// --- End of File ---
