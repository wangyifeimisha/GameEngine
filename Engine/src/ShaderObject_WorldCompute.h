//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_WORLD_COMPUTE_H
#define SHADER_OBJECT_WORLD_COMPUTE_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderObject_WorldCompute : public ShaderObject
	{
	public:

	public:
		ShaderObject_WorldCompute() = delete;
		ShaderObject_WorldCompute(const ShaderObject_WorldCompute &) = delete;
		ShaderObject_WorldCompute &operator = (const ShaderObject_WorldCompute &) = delete;
		virtual ~ShaderObject_WorldCompute();

		ShaderObject_WorldCompute(ShaderObject_WorldCompute::Name _name);


		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------


	};
}

#endif

// --- End of File ---
