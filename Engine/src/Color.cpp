//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Color.h"

namespace Azul
{

	Color::Color(float red, float green, float blue, float alpha)
	{
		assert(red >= 0.0f);
		assert(green >= 0.0f);
		assert(blue >= 0.0f);
		assert(alpha >= 0.0f);

		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	Color::Color()
	{
		this->red = 0.0f;
		this->green = 0.0f;
		this->blue = 0.0f;
		this->alpha = 1.0f;
	}

	void Color::Set(float _red, float _green, float _blue, float _alpha)
	{
		this->red = _red;
		this->green = _green;
		this->blue = _blue;
		this->alpha = _alpha;
	}

	void Color::Set(const Color &r)
	{
		this->red = r.red;
		this->green = r.green;
		this->blue = r.blue;
		this->alpha = r.alpha;
	}

	Color::~Color()
	{

	}

}

//--- End of File ---
