//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "Vec3Data.h"

namespace Azul
{
	Vec3Data::~Vec3Data()
	{

	}

	Vec3Data::Vec3Data()
		:x(0.0f),
		y(0.0f),
		z(0.0f)
	{

	}

	Vec3Data::Vec3Data(Vec3 &r)
		:x(r.x()),
		y(r.y()),
		z(r.z())
	{

	}

	Vec3Data::Vec3Data(float _x, float _y, float _z)
		:x(_x),
		y(_y),
		z(_z)
	{

	}


	void Vec3Data::set(Vec3 &r)
	{
		this->x = r.x();
		this->y = r.y();
		this->z = r.z();
	}

	void Vec3Data::set(float _x, float _y, float _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	void Vec3Data::Serialize(Vec3Data_proto &out) const
	{
		AZUL_UNUSED_VAR(out);
		out.set_x(this->x);
		out.set_y(this->y);
		out.set_z(this->z);
	}

	void Vec3Data::Deserialize(const Vec3Data_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		this->x = in.x();
		this->y = in.y();
		this->z = in.z();
	}

	void Vec3Data::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);

		Trace::out("{%f, %f, %f },\n", this->x, this->y, this->z);
	}
}

// --- End of File ---


