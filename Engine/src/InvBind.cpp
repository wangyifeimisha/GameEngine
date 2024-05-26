//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "InvBind.h"
#include "StringThis.h"

namespace Azul
{
	// public methods: -------------------------------------------------------------

	InvBind::InvBind()
		: mName{InvBind::Name::Not_Initialized},
		numMat{0},
		poInvBindArray{nullptr}
	{
	}

	InvBind::~InvBind()
	{
		delete[] this->poInvBindArray;
		this->poInvBindArray = nullptr;
	}

	void InvBind::Set(InvBind::Name _name, unsigned int _numMat, Mat4 *_poInvBindArray)
	{
		this->mName = _name;
		this->numMat = _numMat;

		this->poInvBindArray = new Mat4[numMat]();
		size_t totalBytes = sizeof(Mat4) * numMat;
		memcpy_s(poInvBindArray, totalBytes, _poInvBindArray, totalBytes);
	}

	bool InvBind::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		InvBind *pDataB = (InvBind *)pTarget;

		bool status = false;

		if(this->mName == pDataB->mName)
		{
			status = true;
		}

		return status;
	}

	void InvBind::Dump()
	{
		Trace::out("      InvBind(%p)\n", this);
		Trace::out("      Name: %s \n", StringMe(this->mName));

		DLink::Dump();
	}

	void InvBind::Wash()
	{
		this->mName = InvBind::Name::Not_Initialized;
		this->numMat = 0;
		// just in case
		delete[] this->poInvBindArray;
		this->poInvBindArray = nullptr;
	}
}

//--- End of File ---
