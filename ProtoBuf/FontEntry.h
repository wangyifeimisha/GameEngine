//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef FONT_ENTRY_H
#define FONT_ENTRY_H

#include "MathEngine.h"
#include "FontEntry.pb.h"

namespace Azul
{
	class FontEntry
	{
	public:
		FontEntry();
		FontEntry(const FontEntry &) = delete;
		FontEntry &operator = (const FontEntry &) = default;
		~FontEntry();

		FontEntry(unsigned int key, float x, float y, float width, float height);
		void set(unsigned int key, float x, float y, float width, float height);

		// Serialization 
		void Serialize(FontEntry_proto &out) const;
		void Deserialize(const FontEntry_proto &in);

		void Print(const char *const pName) const;

	public:
		unsigned int key;
		float x;
		float y;
		float width;
		float height;
	};

}

#endif

// --- End of File ---
