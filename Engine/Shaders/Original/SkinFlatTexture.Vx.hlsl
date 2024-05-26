//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// Enable data
#define SRV_BoneWorldIn
#define SRV_InvBind
#define CBV_ProjectionMatrix
#define CBV_ViewMatrix
#define CBV_WorldMatrix

#include "ShaderMappings.hlsli"

// ------------------------------------------------------
// Sematics Vertex Input:
//      POSITION, TEXCOORD, BLENDWEIGHT, BLENDINDICES
// ------------------------------------------------------

struct AppData_pos  //  vertex constant buffer, slot 0 (VertexSlot::Position)
{
    float3 position : POSITION;
};

struct AppData_tex  // vertex constant buffer, slot 3 (VertexSlot::TexCoord)
{
    float2 tex : TEXCOORD; // uv location
};

struct AppData_weights  // vertex constant buffer, slot 4 (VertexSlot::Weights)
{
    float4 w : BLENDWEIGHT; // weight location
};

struct AppData_joints  // vertex constant buffer, slot 5 (VertexSlot::Joints)
{
    uint4 j : BLENDINDICES; // joints location
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
VertexShaderOutput SkinFlatTexture_Main(AppData_pos inPos,
                                        AppData_tex inTex,
                                        AppData_weights inWeight,
                                        AppData_joints inJoint)
{
    VertexShaderOutput outValue;

    row_major matrix skinWorld = mul(mul(InvBind[inJoint.j.x].m, BoneWorldIn[inJoint.j.x].m), inWeight.w.x) +
	                             mul(mul(InvBind[inJoint.j.y].m, BoneWorldIn[inJoint.j.y].m), inWeight.w.y) +
                                 mul(mul(InvBind[inJoint.j.z].m, BoneWorldIn[inJoint.j.z].m), inWeight.w.z) +
                                 mul(mul(InvBind[inJoint.j.w].m, BoneWorldIn[inJoint.j.w].m), inWeight.w.w);
    
    // M = world * Skin* view * Proj
    row_major matrix Mat = mul(mul(mul(skinWorld, WorldMatrix), ViewMatrix), ProjectionMatrix);
	
    //  out = pos * world * Skin * View * Proj
    outValue.position = mul(float4(inPos.position, 1.0f), Mat);
    outValue.tex = inTex.tex;

    return outValue;
}

// --- End of File ---
