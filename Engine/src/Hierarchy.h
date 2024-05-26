//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "DLink.h"

namespace Azul
{
	class Hierarchy : public DLink
	{
	public:
		enum Name
		{
			ChickenBot,
			Mouse,
			Not_Initialized
		};

	public:
		// public methods: -------------------------------------------------------------
		Hierarchy();
		Hierarchy(const Hierarchy &) = delete;
		Hierarchy &operator = (const Hierarchy &) = delete;
		virtual ~Hierarchy();

		virtual bool Compare(DLink *pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

		void Set(Hierarchy::Name skelName, unsigned int numBones, unsigned int _depth, int *poHierarchyTable);

	public:
		Name          mName;
		unsigned int  numBones;
		unsigned int  depth;
		int          *poTableArray;

	};
}

#endif

//--- End of File ---
