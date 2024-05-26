//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "TextureObject.h"
#include "Engine.h"
#include "StringThis.h"

#include <Windows.h>
#include <string>
#include <d3d11.h>

#include "DirectXDeviceMan.h"

namespace Azul
{
	TextureObject::TextureObject()
		:
		mName(TextureObject::Name::Uninitialized),
		width(0),
		height(0),
		TexResourceSlot(0),
		SamplerSlot(0),
		poTextureRV(nullptr),
		poSampler(nullptr),
		AlphaEnabled(false)
	{

	}

	bool TextureObject::HasAlpha() const
	{
		return this->AlphaEnabled;
	}

	TextureObject::~TextureObject()
	{
		SafeRelease(poTextureRV);
		SafeRelease(poSampler);
	}

	void TextureObject::ActivateTexture()
	{
		DirectXDeviceMan::GetContext()->PSSetShaderResources(TexResourceSlot, 1, &poTextureRV);
		DirectXDeviceMan::GetContext()->PSSetSamplers(SamplerSlot, 1, &poSampler);
	}

	void TextureObject::SetName(TextureObject::Name _name)
	{
		this->mName = _name;
	}

	char *TextureObject::GetName()
	{
		// todo - Hack understand why is this needed for print and fix...
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->mName));
		return pTmp;
	}
}

// --- End of File ---
