//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef FONT_DATA_H
#define FONT_DATA_H

#include "ProtoVersion.h"
#include "FontEntry.h"
#include "FontData.pb.h"

namespace Azul
{
	class FontData
	{
	public:
		FontData();
		FontData(const FontData &) = delete;
		FontData &operator = (const FontData &);
		~FontData();

		FontData(unsigned int _numKeys);

		// Serialization 
		void Serialize(FontData_proto &out) const;
		void Deserialize(const FontData_proto &in);

		void Print(const char *const pName) const;

	public:
		char          pVersion[protoVersion::VERSION_NUM_BYTES];
		unsigned int  numKeys;
		FontEntry    *poFontEntry;
	};

}

#endif

// --- End of File ---
