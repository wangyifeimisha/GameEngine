//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_MIXER_COMPUTE_H
#define SHADER_OBJECT_MIXER_COMPUTE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_MixerCompute : public ShaderObject
	{
	public:

	public:
		ShaderObject_MixerCompute() = delete;
		ShaderObject_MixerCompute(const ShaderObject_MixerCompute &) = delete;
		ShaderObject_MixerCompute &operator = (const ShaderObject_MixerCompute &) = delete;
		virtual ~ShaderObject_MixerCompute();

		ShaderObject_MixerCompute(ShaderObject_MixerCompute::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
