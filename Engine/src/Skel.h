//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SKEL_H
#define SKEL_H

#include "DLink.h"
#include "SkelData.h"

namespace Azul
{
	class Skel : public DLink
	{
	public:
		static const unsigned int SKELETON_NAME_SIZE = 64;

		enum Name
		{
			ChickenBot,
			Mouse,
			Not_Initialized
		};

		struct Data
		{
			int  index;
			int  parentIndex;
			char name[SKELETON_NAME_SIZE];
		};

	public:
		// public methods: -------------------------------------------------------------
		Skel();
		Skel(const Skel &) = delete;
		Skel &operator = (const Skel &) = delete;
		virtual ~Skel();


		virtual bool Compare(DLink *pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

		void Set(Skel::Name skelName, unsigned int numBones, SkelEntry *poSkelEntry);

	public:
		Name           mName;
		unsigned int   numBones;
		Data          *poTableArray;

	};

}


#endif

//--- End of File ---
