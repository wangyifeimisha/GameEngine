//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef HIERARCHY_PROTO_H
#define HIERARCHY_PROTO_H

#include "Hierarchy.h"

namespace Azul
{
	class HierarchyProto
	{
	public:
		// Data
		HierarchyProto(const char *const pFileName, Hierarchy::Name skelName);

		HierarchyProto() = delete;
		HierarchyProto(const HierarchyProto &) = delete;
		HierarchyProto &operator = (HierarchyProto &) = delete;
		virtual ~HierarchyProto();

	};
}

#endif

//--- End of File ---

