//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "QuatData.h"

namespace Azul
{
	QuatData::~QuatData()
	{

	}

	QuatData::QuatData()
		:qx(0.0f),
		qy(0.0f),
		qz(0.0f),
		qw(1.0f)
	{

	}

	QuatData::QuatData(Quat &r)
		:qx(r.qx()),
		qy(r.qy()),
		qz(r.qz()),
		qw(r.real())
	{

	}

	QuatData::QuatData(float _x, float _y, float _z, float _w)
		:qx(_x),
		qy(_y),
		qz(_z),
		qw(_w)
	{

	}

	void QuatData::set(Quat &r)
	{
		this->qx = r.qx();
		this->qy = r.qy();
		this->qz = r.qz();
		this->qw = r.real();
	}

	void QuatData::set(float _x, float _y, float _z, float _w)
	{
		this->qx = _x;
		this->qy = _y;
		this->qz = _z;
		this->qw = _w;
	}

	void QuatData::Serialize(QuatData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);
		out.set_qx(this->qx);
		out.set_qy(this->qy);
		out.set_qz(this->qz);
		out.set_qw(this->qw);
	}

	void QuatData::Deserialize(const QuatData_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		this->qx = in.qx();
		this->qy = in.qy();
		this->qz = in.qz();
		this->qw = in.qw();
	}

	void QuatData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);

		Trace::out("{%f, %f, %f, %f },\n", this->qx, this->qy, this->qz, this->qw);
	}
}

// --- End of File ---


