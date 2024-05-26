//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject.h"
#include "Engine.h"
#include "StringThis.h"
#include "DirectXDeviceMan.h"

namespace Azul
{
	ShaderObject::ShaderObject(ShaderObject::Name _name)
		:
		name(_name),
		poInputLayout{nullptr},
		poVertexShader{nullptr},
		poPixelShader{nullptr},
		poComputeShader{nullptr}
	{

	}

	ShaderObject::~ShaderObject()
	{
		SafeRelease(poInputLayout);
		SafeRelease(poVertexShader);
		SafeRelease(poPixelShader);
		SafeRelease(poComputeShader);
	}

	void ShaderObject::ActivateShader()
	{
		DirectXDeviceMan::GetContext()->VSSetShader(poVertexShader, nullptr, 0);
		DirectXDeviceMan::GetContext()->IASetInputLayout(poInputLayout);
		DirectXDeviceMan::GetContext()->PSSetShader(poPixelShader, nullptr, 0);
	}

	void ShaderObject::ActivateCSShader()
	{
		DirectXDeviceMan::GetContext()->CSSetShader(poComputeShader, nullptr, 0);
	}

	void ShaderObject::SetName(ShaderObject::Name _name)
	{
		this->name = _name;
	}

	char *ShaderObject::GetName()
	{
		// todo - Hack understand why is this needed for print and fix...
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->name));
		return pTmp;
	}

	// -----------------------------------------------------------
	// Get the latest profile for the specified vertex shader type.
	// -----------------------------------------------------------
	const char *ShaderObject::GetLatestProfile_VertexShader() const
	{
		// Query the current feature level:
		D3D_FEATURE_LEVEL featureLevel = DirectXDeviceMan::GetDevice()->GetFeatureLevel();

		switch(featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1:
		case D3D_FEATURE_LEVEL_11_0:
		{
			return "vs_5_0";
		}
		break;

		case D3D_FEATURE_LEVEL_10_1:
		{
			return "vs_4_1";
		}
		break;

		case D3D_FEATURE_LEVEL_10_0:
		{
			return "vs_4_0";
		}
		break;

		case D3D_FEATURE_LEVEL_9_3:
		{
			return "vs_4_0_level_9_3";
		}
		break;

		case D3D_FEATURE_LEVEL_9_2:
		case D3D_FEATURE_LEVEL_9_1:
		{
			return "vs_4_0_level_9_1";
		}
		break;

		default:
			assert(false);

		}

		return "";
	}

	// -----------------------------------------------------------
	// Get the latest profile for the specified compute shader type.
	// -----------------------------------------------------------
	const char *ShaderObject::GetLatestProfile_ComputeShader() const
	{
		// Query the current feature level:
		D3D_FEATURE_LEVEL featureLevel = DirectXDeviceMan::GetDevice()->GetFeatureLevel();

		// Prefer higher CS shader profile when possible as CS 5.0 
		//        provides better performance on 11-class hardware.

		switch(featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1:
		case D3D_FEATURE_LEVEL_11_0:
		{
			return "cs_5_0";
		}
		break;

		case D3D_FEATURE_LEVEL_10_1:
		case D3D_FEATURE_LEVEL_10_0:
		{
			return "cs_4_0";
		}
		break;


		default:
			assert(false);

		}

		return "";
	}


	// -----------------------------------------------------------
	// Get the latest profile for the specified pixel shader type.
	// -----------------------------------------------------------
	const char *ShaderObject::GetLatestProfile_PixelShader() const
	{
		// Query the current feature level:
		D3D_FEATURE_LEVEL featureLevel = DirectXDeviceMan::GetDevice()->GetFeatureLevel();
		switch(featureLevel)
		{
		case D3D_FEATURE_LEVEL_11_1:
		case D3D_FEATURE_LEVEL_11_0:
		{
			return "ps_5_0";
		}
		break;
		case D3D_FEATURE_LEVEL_10_1:
		{
			return "ps_4_1";
		}
		break;
		case D3D_FEATURE_LEVEL_10_0:
		{
			return "ps_4_0";
		}
		break;
		case D3D_FEATURE_LEVEL_9_3:
		{
			return "ps_4_0_level_9_3";
		}
		break;
		case D3D_FEATURE_LEVEL_9_2:
		case D3D_FEATURE_LEVEL_9_1:
		{
			return "ps_4_0_level_9_1";
		}
		break;
		}
		return "";
	}

	void ShaderObject::CreateComputeShader(const unsigned char *pCompiledComputeShaderObject,
										   size_t codeSize)
	{
		assert(pCompiledComputeShaderObject);

		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateComputeShader(pCompiledComputeShaderObject,
																codeSize,
																nullptr,
																&poComputeShader);
		assert(SUCCEEDED(hr));

		assert(std::string("cs_5_0") == (GetLatestProfile_ComputeShader()));

		assert(poComputeShader);
	}


	void ShaderObject::CreateVertexShader(const unsigned char *pCompiledVertexShaderObject,
										  size_t codeSize)
	{
		assert(pCompiledVertexShaderObject);

		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateVertexShader(pCompiledVertexShaderObject, codeSize, nullptr, &poVertexShader);
		assert(SUCCEEDED(hr));

		assert(std::string("vs_5_0") == (GetLatestProfile_VertexShader()));

		assert(poVertexShader);
	}

	void ShaderObject::CreatePixelShader(const unsigned char *pCompiledPixelShaderObject,
										 size_t codeSize)
	{
		assert(pCompiledPixelShaderObject);

		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreatePixelShader(pCompiledPixelShaderObject, codeSize, nullptr, &poPixelShader);
		assert(SUCCEEDED(hr));

		assert(std::string("ps_5_0") == (GetLatestProfile_PixelShader()));

		assert(poPixelShader);
	}

	void ShaderObject::CreateInputLayout(const unsigned char *pCompiledVertexShaderObject,
										 size_t codeSize,
										 D3D11_INPUT_ELEMENT_DESC *pDesc,
										 unsigned int SizeInBytes)
	{
		assert(pCompiledVertexShaderObject);
		assert(pDesc);

		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateInputLayout(pDesc,
															  SizeInBytes / sizeof(D3D11_INPUT_ELEMENT_DESC),
															  pCompiledVertexShaderObject,
															  codeSize,
															  &poInputLayout);
		assert(SUCCEEDED(hr));

		assert(poInputLayout);
	}
}

// --- End of File ---