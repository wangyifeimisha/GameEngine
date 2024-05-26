//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef Quat_DATA_H
#define Quat_DATA_H

#include "MathEngine.h"
#include "QuatData.pb.h"

namespace Azul
{

	class QuatData
	{
	public:
		QuatData();
		QuatData(const QuatData &) = delete;
		QuatData &operator = (const QuatData &) = default;
		~QuatData();

		QuatData(Quat &r);
		QuatData(float _x, float _y, float _z, float _w);

		void set(Quat &r);
		void set(float _x, float _y, float _z, float _w);

		// Serialization 
		void Serialize(QuatData_proto &out) const;
		void Deserialize(const QuatData_proto &in);

		void Print(const char *const pName) const;

	public:
		float qx;
		float qy;
		float qz;
		float qw;
	};

}

#endif

// --- End of File ---
