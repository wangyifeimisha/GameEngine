//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "BoneEntry.h"

namespace Azul
{
	BoneEntry::~BoneEntry()
	{

	}

	BoneEntry::BoneEntry()
		:S(1, 1, 1),
		Q(0, 0, 0, 1),
		T(1, 1, 1)
	{

	}

	BoneEntry::BoneEntry(Vec3 &s, Quat &q, Vec3 &t)
		: S(s),
		Q(q),
		T(t)
	{

	}

	void BoneEntry::set(Vec3 &s, Quat &q, Vec3 &t)
	{
		this->S.set(s);
		this->Q.set(q);
		this->T.set(t);
	}


	void BoneEntry::Serialize(BoneEntry_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		Vec3Data_proto s_proto;
		this->S.Serialize(s_proto);
		*out.mutable_s() = s_proto;

		QuatData_proto q_proto;
		this->Q.Serialize(q_proto);
		*out.mutable_q() = q_proto;

		Vec3Data_proto t_proto;
		this->T.Serialize(t_proto);
		*out.mutable_t() = t_proto;
	}

	void BoneEntry::Deserialize(const BoneEntry_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		
		this->S.Deserialize(in.s());
		this->Q.Deserialize(in.q());
		this->T.Deserialize(in.t());
	}

	void BoneEntry::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);

		Trace::out("{ \n");
		Trace::out("   {%5.5g, %5.5g, %5.5g },        // S\n", S.x, S.y, S.z);
		Trace::out("   {%5.5g, %5.5g, %5.5g, %5.5g }, // Q\n",Q.qx,Q.qy,Q.qz,Q.qw);
		Trace::out("   {%5.5g, %5.5g, %5.5g },        // T\n", T.x, T.y, T.z);
		Trace::out("} \n");
	}
}

// --- End of File ---


