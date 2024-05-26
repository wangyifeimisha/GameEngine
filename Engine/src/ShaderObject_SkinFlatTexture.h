//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_SKIN_FLAT_TEXTURE_H
#define SHADER_OBJECT_SKIN_FLAT_TEXTURE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_SkinFlatTexture : public ShaderObject
	{
	public:

	public:
		ShaderObject_SkinFlatTexture() = delete;
		ShaderObject_SkinFlatTexture(const ShaderObject_SkinFlatTexture &) = delete;
		ShaderObject_SkinFlatTexture &operator = (const ShaderObject_SkinFlatTexture &) = delete;
		virtual ~ShaderObject_SkinFlatTexture();

		ShaderObject_SkinFlatTexture(ShaderObject_SkinFlatTexture::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
