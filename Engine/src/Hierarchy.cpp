//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Hierarchy.h"
#include "StringThis.h"

namespace Azul
{
	// public methods: -------------------------------------------------------------

	Hierarchy::Hierarchy()
		: mName{Hierarchy::Name::Not_Initialized},
		numBones{0},
		depth{0},
		poTableArray{nullptr}
	{
	}

	Hierarchy::~Hierarchy()
	{
		delete[] this->poTableArray;
		this->poTableArray = nullptr;
	}

	void Hierarchy::Set(Hierarchy::Name hierarchyName, unsigned int _numBones, unsigned int _depth, int *poHierarchyTable)
	{
		this->mName = hierarchyName;
		this->numBones = _numBones;
		this->depth = _depth;

		size_t size = numBones * depth;

		this->poTableArray = new int[size]();
		size_t totalBytes = sizeof(int) * size;
		memcpy_s(poTableArray, totalBytes, poHierarchyTable, totalBytes);
	}

	bool Hierarchy::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Hierarchy *pDataB = (Hierarchy *)pTarget;

		bool status = false;

		if(this->mName == pDataB->mName)
		{
			status = true;
		}

		return status;
	}

	void Hierarchy::Dump()
	{
		Trace::out("      Hierarchy(%p)\n", this);
		Trace::out("      Name: %s \n", StringMe(this->mName));

		DLink::Dump();
	}

	void Hierarchy::Wash()
	{
		this->mName = Hierarchy::Name::Not_Initialized;
		this->numBones = 0;
		this->depth = 0;
		// just in case
		delete[] this->poTableArray;
		this->poTableArray = nullptr;
	}
}

//--- End of File ---
