//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CLIP_PROTO_H
#define CLIP_PROTO_H

#include "Clip.h"

namespace Azul
{
	class ClipProto
	{
	public:
		// Data
		ClipProto(const char *const pFileName, Clip::Name clipName, Skel::Name skelName);

		ClipProto() = delete;
		ClipProto(const ClipProto &) = delete;
		ClipProto &operator = (ClipProto &) = delete;
		virtual ~ClipProto();

	};
}

#endif

//--- End of File ---

