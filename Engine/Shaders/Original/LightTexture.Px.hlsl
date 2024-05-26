//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// Enable data
#define SAMPLER_A
#define SRV_MainTexture

#include "ShaderMappings.hlsli"

// -------------------------------------
//  Pixel Shader Input Sematics
//        TEXCOORD - uv tex coord
// -------------------------------------
struct PixelShaderInput
{
    float2 tex : TEXCOORD;
    float4 color : COLOR;
    float4 position : SV_POSITION;
};

// --------------------------------------------------------
//  Pixel Shader Main()
//      SV_TARGET - System Value Target
//                  output stored in a render target 0  (only one target)
// --------------------------------------------------------
float4 LightTexture_Main( PixelShaderInput inData ) : SV_TARGET
{
	return  inData.color * MainTexture.Sample(A_Sampler, inData.tex);
}


// --- End of File ---
