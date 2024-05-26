//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef INV_BIND_H
#define INV_BIND_H

#include "DLink.h"
#include "Mat4.h"

namespace Azul
{
	class InvBind : public DLink
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
		InvBind();
		InvBind(const InvBind &) = delete;
		InvBind &operator = (const InvBind &) = delete;
		virtual ~InvBind();

		virtual bool Compare(DLink *pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

		void Set(InvBind::Name _name, unsigned int _numMat, Mat4 *_poInvBindArray);

	public:
		Name          mName;
		unsigned int  numMat;
		Mat4          *poInvBindArray;

	};
}

#endif

//--- End of File ---
