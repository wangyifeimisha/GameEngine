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

struct AppData_color  // vertex constant buffer, slot 1 (VertexSlot::Color)
{
	float3 color: COLOR;
};

// ------------------------------------------------------------
// Sematics Vertex Output:
//      COLOR - Input to the Pixel Shader
//      SV_POSIION - System Value goes to the raster stage
// ------------------------------------------------------------
struct VertexShaderOutput
{
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

// ----------------------------------------------------------
//  Vertex Shader Main()
// ----------------------------------------------------------
VertexShaderOutput ColorByVertex_Main(AppData_pos inPos, AppData_color inColor)
{
	VertexShaderOutput outValue;

	// Mat = World * View * Proj
	row_major matrix Mat = mul(mul(WorldMatrix, ViewMatrix), ProjectionMatrix);

	//   position = vec4(inPos.xyz,1) * Mat
	//   color    = vec4(inColor.rgb,1)
	outValue.position = mul(float4(inPos.position, 1.0f), Mat);
	outValue.color = float4(inColor.color, 1.0f);

	return outValue;
}

// --- End of File ---
