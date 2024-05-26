//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef INV_BIND_PROTO_H
#define INV_BIND_PROTO_H

#include "InvBind.h"

namespace Azul
{
	class InvBindProto
	{
	public:
		// Data
		InvBindProto(const char *const pFileName, InvBind::Name skelName);

		InvBindProto() = delete;
		InvBindProto(const InvBindProto &) = delete;
		InvBindProto &operator = (InvBindProto &) = delete;
		virtual ~InvBindProto();

	};
}

#endif

//--- End of File ---

