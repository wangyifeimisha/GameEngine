//----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef INV_BIND_DATA_H
#define INV_BIND_DATA_H

#include "InvBindData.pb.h"
#include "ProtoVersion.h"

namespace Azul
{
	class InvBindData
	{
	public:
		InvBindData();
		InvBindData(const InvBindData &) = delete;
		InvBindData &operator = (const InvBindData &);
	   ~InvBindData();

		InvBindData(unsigned int _numMat);

		// Serialization 
		void Serialize(InvBindData_proto &out) const;
		void Deserialize(const InvBindData_proto &in);

		void Print(const char *const pName) const;

	public:
		char pVersion[protoVersion::VERSION_NUM_BYTES];
		unsigned int numMat;
		float *poData;
	};

}

#endif

// --- End of File ---
