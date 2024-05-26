//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H

#include <d3d11.h>

namespace Azul
{
	class TextureObject
	{
	public:
		enum class Name
		{
			NullTexture,
			Duckweed,
			Brick,
			Stone,
			Rocks,
			Crate,
			SpaceFrigate,
			ChickenBot,
			Test0,
			Test1,
			Test2,
			Test3,
			FontAriel36,
			R2D2,
			Mouse,
			Uninitialized
		};

	public:
		TextureObject();
		TextureObject(const TextureObject &) = delete;
		TextureObject &operator = (const TextureObject &) = delete;
		virtual ~TextureObject();

		TextureObject(LPCWSTR filepath,
					  D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

		void ActivateTexture();

		bool HasAlpha() const;

		char *GetName();
		void SetName(TextureObject::Name _name);

	protected:


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------
	public:
		TextureObject::Name mName;

		unsigned int    width;
		unsigned int    height;
		int             TexResourceSlot;
		int             SamplerSlot;

		ID3D11ShaderResourceView *poTextureRV;
		ID3D11SamplerState *poSampler;

		bool AlphaEnabled;
	};
}

#endif

// --- End of File ---
