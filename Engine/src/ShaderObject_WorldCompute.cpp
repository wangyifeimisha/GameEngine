//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_WorldCompute.h"
#include "Mesh.h"

// User generated headers... 
#include "World.Cx.h"

namespace Azul
{
	ShaderObject_WorldCompute::~ShaderObject_WorldCompute()
	{

	}

	ShaderObject_WorldCompute::ShaderObject_WorldCompute(ShaderObject_WorldCompute::Name _name)
		: ShaderObject(_name)
	{
		this->CreateComputeShader(g_World_CxShader, sizeof(g_World_CxShader));
	}

}

// --- End of File ---
