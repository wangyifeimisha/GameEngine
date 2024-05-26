//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_MAPPINGS_H
#define SHADER_MAPPINGS_H

namespace Azul
{
	enum class VertexSlot : uint32_t
	{
		Position,  //0
		Color,     //1
		Norm,      //2
		TexCoord,  //3
		Weights,   //4
		Joints     //5

	};

	// in shaders these are CBV slot "bx"
	enum class ConstantBufferSlot : uint32_t
	{
		vsProjection,   //0
		vsView,         //1
		vsWorld,        //2

		vsLightColor,   //3
		vsLightPos,		//4

		psUV_Correction, //5
		psSpriteColor,	 //6	

		vsInvBind,       //7
		vsBoneWorld,     //8

		csMixer,          //9
		csWorld			 //10
	};

	// in shaders these are RSV slot "tx"
	enum class ShaderResourceBufferSlot : uint32_t
	{
		Texture,		 // 0
		KeyA,            // 1  
		KeyB,            // 2  
		HierarchyTable,  // 3
		BoneWorldIn,     // 4
		InvBind          // 5
	};

	// in shaders these are UAV slot "ux"
	enum class UnorderedAccessBufferSlot : uint32_t
	{
		MixerABOut,    // slot 0  
		BoneWorldOut   // slot 1  
	};
}

#endif

// --- End of File ---
