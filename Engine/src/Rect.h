//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef RECT_H
#define RECT_H

namespace Azul
{
	struct Rect
	{
		Rect();
		Rect(const Rect &) = default;
		Rect &operator = (const Rect &) = default;
		~Rect() = default;

		Rect(float x, float y, float width, float height);
		void Set(float x, float y, float width, float height);
		void clear();

		float x;
		float y;
		float width;
		float height;
	};
}

#endif

// --- End of File ---
