//----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef JOINT_DATA_H
#define JOINT_DATA_H

#include "JointData.pb.h"
#include "ProtoVersion.h"

namespace Azul
{
	class JointData
	{
	public:
		JointData();
		JointData(const JointData &) = delete;
		JointData &operator = (const JointData &);
	   ~JointData();

		JointData(unsigned int _numJoints);

		// Serialization 
		void Serialize(JointData_proto &out) const;
		void Deserialize(const JointData_proto &in);

		void Print(const char *const pName) const;

	public:
		char  pVersion[protoVersion::VERSION_NUM_BYTES];
		unsigned int numJoints;
		unsigned int *poData;
	};

}

#endif

// --- End of File ---
