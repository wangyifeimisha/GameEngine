//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COLOR_H
#define COLOR_H


namespace Azul
{
	class Color
	{
	public:
		Color();
		Color(const Color &r) = default;
		Color &operator=(const Color &) = default;
		Color(float red, float green, float blue, float alpha = 1.0f);
		virtual ~Color();

		void Set(float red, float green, float blue, float alpha = 1.0f);
		void Set(const Color &r);

		float red;
		float green;
		float blue;
		float alpha;

	private:

	};
}

#endif

//--- End of File ---
