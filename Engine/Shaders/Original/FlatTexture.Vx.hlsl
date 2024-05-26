//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// Enable data
#define CBV_ProjectionMatrix
#define CBV_ViewMatrix
#define CBV_WorldMatrix

#include "ShaderMappings.hlsli"

// ------------------------------------------------------
// Sematics Vertex Input:
//      POSITION - used in vertex layout description
//      COLOR - used in vertex layout description
// ------------------------------------------------------

struct AppData_pos  //  vertex constant buffer, slot 0 (VertexSlot::Position)
{
	float3 position : POSITION;
};

struct AppData_tex  // vertex constant buffer, slot 3 (VertexSlot::TexCoord)
{
	float2 tex: TEXCOORD;  // uv location
};

// ------------------------------------------------------------
// Sematics Vertex Output:
//      COLOR - Input to the Pixel Shader
//      SV_POSIION - System Value goes to the raster stage
// ------------------------------------------------------------
struct VertexShaderOutput
{
	float2 tex : TEXCOORD;
	float4 position : SV_POSITION;
};

// ----------------------------------------------------------
//  Vertex Shader Main()
// ----------------------------------------------------------
VertexShaderOutput FlatTexture_Main(AppData_pos inPos, AppData_tex inTex)
{
	VertexShaderOutput outValue;

	// Mat = World * View * Proj
	row_major matrix Mat = mul(mul(WorldMatrix, ViewMatrix), ProjectionMatrix);

	//   position = vec4(inPos.xyz,1) * Mat
	//   color    = vec4(inColor.rgb,1)
	outValue.position = mul(float4(inPos.position, 1.0f), Mat);
	outValue.tex = inTex.tex;

	return outValue;
}

// --- End of File ---
