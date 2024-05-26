//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_SkinFlatTexture.h"
#include "MeshLayout.h"
#include "ShaderMappings.h"

// User generated headers... 
#include "SkinFlatTexture.Px.h"
#include "SkinFlatTexture.Vx.h"
        
namespace Azul
{
	ShaderObject_SkinFlatTexture::~ShaderObject_SkinFlatTexture()
	{

	}

	ShaderObject_SkinFlatTexture::ShaderObject_SkinFlatTexture(ShaderObject_SkinFlatTexture::Name _name)
		: ShaderObject(_name)
	{
		this->CreateVertexShader(g_SkinFlatTexture_VxShader, sizeof(g_SkinFlatTexture_VxShader));

		// Create the input layout for the vertex shader.
		D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Position, offsetof(VertexPos,Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, (uint32_t)VertexSlot::TexCoord, offsetof(VertexTexCoord,TexCoord),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT , (uint32_t)VertexSlot::Weights, offsetof(VertexWeights,Weight),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT  , (uint32_t)VertexSlot::Joints, offsetof(VertexJoints,Joint),  D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		this->CreateInputLayout(g_SkinFlatTexture_VxShader,
								sizeof(g_SkinFlatTexture_VxShader),
								vertexLayoutDesc,
								sizeof(vertexLayoutDesc));

		this->CreatePixelShader(g_SkinFlatTexture_PxShader,
								sizeof(g_SkinFlatTexture_PxShader));



	}

}

// --- End of File ---
