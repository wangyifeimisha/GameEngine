//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef TEXTURE_PROTO_H
#define TEXTURE_PROTO_H

#include "TextureObject.h"

namespace Azul
{
	class TextureProto : public TextureObject
	{
	public:
		TextureProto() = delete;
		TextureProto(const TextureProto &) = delete;
		TextureProto &operator = (const TextureProto &) = delete;
		virtual ~TextureProto();

		TextureProto(const char *const pMeshFileName,
					 D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------

		ID3D11Texture2D *poTex;
	};
}

#endif

// --- End of File ---
