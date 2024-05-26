//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ITERATOR_H
#define ITERATOR_H

#include "DLink.h"

namespace Azul
{
	class Iterator
	{
	public:
		virtual DLink *Next() = 0;
		virtual bool IsDone() = 0;
		virtual DLink *First() = 0;
		virtual DLink *Curr() = 0;
	};
}

#endif

// --- End of File ---
