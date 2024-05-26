//----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "JointData.h"

namespace Azul
{
	JointData::~JointData()
	{
		delete[] this->poData;
		this->poData = nullptr;
	}

	JointData::JointData()
		:pVersion{0}, 
		numJoints(0),
		poData(nullptr)
	{
		strcpy_s(this->pVersion, protoVersion::VERSION_NUM_BYTES, protoVersion::VERSION_STRING);
		assert(strlen(this->pVersion) < protoVersion::VERSION_NUM_BYTES);
	}

	JointData::JointData(unsigned int _numJoints)
		:pVersion{0}, 
		numJoints(_numJoints),
		poData(nullptr)
	{
		strcpy_s(this->pVersion, protoVersion::VERSION_NUM_BYTES, protoVersion::VERSION_STRING);
		assert(strlen(this->pVersion) < protoVersion::VERSION_NUM_BYTES);

		this->poData = new unsigned int[numJoints]();
		assert(this->poData);
	}

	JointData &JointData::operator = (const JointData &r)
	{
		if(this != &r)
		{
			// Nuke orginal
			this->numJoints = 0;
			delete[] this->poData;

			// copy the new
			this->numJoints = r.numJoints;
			this->poData = new unsigned int[numJoints]();

			for(size_t i = 0; i < (numJoints); i++)
			{
				this->poData[i] = r.poData[i];
			}
		}

		return *this;
	}

	void JointData::Serialize(JointData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		std::string sVersion((const char *)this->pVersion, protoVersion::VERSION_NUM_BYTES);
		out.set_pversion(sVersion);

		out.set_numjoints(this->numJoints);
	
		for(unsigned int i = 0; i < (numJoints); i++)
		{
			// add it to the message(package)
			out.add_podata(this->poData[i]);
		}
	}

	void JointData::Deserialize(const JointData_proto &in)
	{
		AZUL_UNUSED_VAR(in);

		// CHECK the Version
		memcpy_s(this->pVersion, protoVersion::VERSION_NUM_BYTES, in.pversion().data(), protoVersion::VERSION_NUM_BYTES);
		assert(strcmp(this->pVersion, protoVersion::VERSION_STRING) == 0);

		// Safety
		delete[] this->poData;
		this->poData = nullptr;

		this->numJoints = in.numjoints();

		this->poData = new unsigned int[(numJoints)]();
		assert(this->poData);

		for(unsigned int i = 0; i < (numJoints); i++)
		{
			poData[i] = in.podata(i);
		}
	}

	void JointData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		Trace::out("%s: \n", pName);

		Trace::out("numJoints: %d\n",this->numJoints);


		for(size_t i = 0; i < (numJoints); i++)
		{
			Trace::out("%2d: %2d \n",i, this->poData[i]);
		}

		Trace::out("\n");
	}
}

// --- End of File ---


