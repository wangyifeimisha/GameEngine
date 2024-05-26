//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_Sprite.h"
#include "MeshLayout.h"
#include "ShaderMappings.h"

// User generated headers... 
#include "Sprite.Px.h"
#include "Sprite.Vx.h"

namespace Azul
{
	ShaderObject_Sprite::~ShaderObject_Sprite()
	{

	}

	ShaderObject_Sprite::ShaderObject_Sprite(ShaderObject_Sprite::Name _name)
		: ShaderObject(_name)
	{
		this->CreateVertexShader(g_Sprite_VxShader, sizeof(g_Sprite_VxShader));

		// Create the input layout for the vertex shader.
		D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t)VertexSlot::Position, offsetof(VertexPos,Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD"   , 0, DXGI_FORMAT_R32G32_FLOAT, (uint32_t)VertexSlot::TexCoord, offsetof(VertexTexCoord,TexCoord),  D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		this->CreateInputLayout(g_Sprite_VxShader, sizeof(g_Sprite_VxShader), vertexLayoutDesc, sizeof(vertexLayoutDesc));

		this->CreatePixelShader(g_Sprite_PxShader, sizeof(g_Sprite_PxShader));

	}

}

// --- End of File ---
