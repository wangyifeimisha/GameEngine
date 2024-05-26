//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_SPRITE_H
#define SHADER_OBJECT_SPRITE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_Sprite : public ShaderObject
	{
	public:

	public:
		ShaderObject_Sprite() = delete;
		ShaderObject_Sprite(const ShaderObject_Sprite &) = delete;
		ShaderObject_Sprite &operator = (const ShaderObject_Sprite &) = delete;
		~ShaderObject_Sprite();

		ShaderObject_Sprite(ShaderObject_Sprite::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
