//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "TextureProto.h"
#include "File.h"
#include "textureData.h"

#include "Engine.h"
#include "StringThis.h"

#include <Windows.h>
#include <string>
#include <d3d11.h>

#include "DirectXDeviceMan.h"

namespace Azul
{
	TextureProto::TextureProto(const char *const pMeshFileName,
							   D3D11_FILTER filter)
		: TextureObject(),
		poTex(nullptr)
	{
		// ----------------------------------------------
		// READ the data from the file ONLY
		// ----------------------------------------------

		// File stuff
		File::Handle fh;
		File::Error  ferror;

		ferror = File::Open(fh, pMeshFileName, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);

		// Get the size
		ferror = File::Seek(fh, File::Position::END, 0);
		assert(ferror == File::Error::SUCCESS);

		DWORD length;
		ferror = File::Tell(fh, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Position::BEGIN, 0);
		assert(ferror == File::Error::SUCCESS);

		char *poBuff = new char[length];
		assert(poBuff);

		ferror = File::Read(fh, poBuff, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		// Now the raw data is poBUff
		std::string strIn(poBuff, length);
		textureData_proto mB_proto;

		mB_proto.ParseFromString(strIn);

		textureData mB;
		mB.Deserialize(mB_proto);

		delete[] poBuff;

		// Do I know this format?
		assert(strcmp(mB.pVersion, "1.0.5") == 0);

		//----------------------

		// Create texture
		HRESULT hr;

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = mB.width;
		desc.Height = mB.height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;

		// w1(7)
		this->width = mB.width;;
		this->height = mB.height;;

		if(mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA
		   || mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA)
		{
			this->AlphaEnabled = true;
		}
		else
		{
			this->AlphaEnabled = false;
		}

		assert((mB.textType == textureData::TEXTURE_TYPE::PNG)
			   || (mB.textType == textureData::TEXTURE_TYPE::TGA));


		desc.Format = DXGI_FORMAT_UNKNOWN;

		if(mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB
		   || mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA)
		{
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		}


		if(mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR
		   || mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA)
		{
		desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		}

		assert(desc.Format != DXGI_FORMAT_UNKNOWN);


		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = mB.poData;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;

		hr = DirectXDeviceMan::GetDevice()->CreateTexture2D(&desc, &subResource, &poTex);

		//----------------------

		if(SUCCEEDED(hr) && poTex != nullptr)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
			memset(&SRVDesc, 0, sizeof(SRVDesc));

			SRVDesc.Format = DXGI_FORMAT_UNKNOWN;

			if(mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB
			   || mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA)
			{
			SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			}


			if(mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR
			   || mB.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA)
			{
			SRVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			}

			assert(SRVDesc.Format != DXGI_FORMAT_UNKNOWN);

			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			SRVDesc.Texture2D.MipLevels = 1;

			hr = DirectXDeviceMan::GetDevice()->CreateShaderResourceView(poTex, &SRVDesc, &poTextureRV);
			assert(SUCCEEDED(hr));
		}
		else
		{
			assert(false);
		}

		//-----------------------------------

		// Create the sample state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = filter;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		hr = DirectXDeviceMan::GetDevice()->CreateSamplerState(&sampDesc, &poSampler);
		assert(SUCCEEDED(hr));
	}


	TextureProto::~TextureProto()
	{
		SafeRelease(poTex);
	}

}

// --- End of File ---
