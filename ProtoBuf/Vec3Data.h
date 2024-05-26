//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef Vec3_DATA_H
#define Vec3_DATA_H

#include "MathEngine.h"
#include "Vec3Data.pb.h"

namespace Azul
{

	class Vec3Data
	{
	public:
		Vec3Data();
		Vec3Data(const Vec3Data &) = delete;
		Vec3Data &operator = (const Vec3Data &) = default;
		~Vec3Data();

		Vec3Data(Vec3 &r);
		Vec3Data(float _x, float _y, float _z);

		void set(Vec3 &r);
		void set(float _x, float _y, float _z);

		// Serialization 
		void Serialize(Vec3Data_proto &out) const;
		void Deserialize(const Vec3Data_proto &in);

		void Print(const char *const pName) const;

	public:
		float x;
		float y;
		float z;
	};

}

#endif

// --- End of File ---
