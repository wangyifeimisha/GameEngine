//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DLINK_H
#define DLINK_H

namespace Azul
{
	class DLink
	{
	public:

		DLink();
		DLink(const DLink &) = default;
		DLink &operator = (const DLink &) = default;
		virtual ~DLink() = default;


		virtual void Wash() = 0;

		// Becomes optional with a virtual with default implementation
		virtual char *GetName()
		{
			return nullptr;
		}

		virtual bool Compare(DLink *pTargetNode) = 0;

		void Clear();
		virtual void Dump();


		// Data: -----------------------------
		DLink *pNext;
		DLink *pPrev;

	};
}

#endif

// --- End of File ---
