//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_MixerCompute.h"
#include "Mesh.h"

// User generated headers... 
#include "Mixer.Cx.h"

namespace Azul
{
	ShaderObject_MixerCompute::~ShaderObject_MixerCompute()
	{

	}

	ShaderObject_MixerCompute::ShaderObject_MixerCompute(ShaderObject_MixerCompute::Name _name)
		: ShaderObject(_name)
	{
		this->CreateComputeShader(g_Mixer_CxShader, sizeof(g_Mixer_CxShader));
	}

}

// --- End of File ---
