//--------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

struct BoneType
{
    float4 t;
    float4 q;
    float4 s;
};

struct rowMatrix
{
    row_major matrix m;
};

// ------------------------------------------
// sx - s is sampler, x - slot
// ------------------------------------------

#ifdef SAMPLER_A
    SamplerState A_Sampler : register(s0);
#endif

// --------------------------------------------------
// tx - t is input shader resource views (SRV), x - slot
//      max count == 128
//      https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/registers---cs-5-0
// --------------------------------------------------

#ifdef SRV_MainTexture
    Texture2D MainTexture : register(t0);
#endif

#ifdef SRV_KeyA
    StructuredBuffer<BoneType> KeyA : register(t1); 
#endif

#ifdef SRV_KeyB
    StructuredBuffer<BoneType> KeyB : register(t2);   
#endif

#ifdef SRV_HierarchyTable   
    StructuredBuffer<int> HierarchyTable : register(t3); 
#endif

#ifdef SRV_BoneWorldIn
    StructuredBuffer<rowMatrix> BoneWorldIn : register(t4); 
#endif

#ifdef SRV_InvBind
    StructuredBuffer<rowMatrix> InvBind : register(t5); 
#endif

// ----------------------------------------------------
// ux - u is  unordered access views (UAV), x - slot
//      max count == 8
//      https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/registers---cs-5-0
// ----------------------------------------------------

#ifdef UAV_MixerABOut 
    RWStructuredBuffer<BoneType> MixerABOut : register(u0); // (UnorderedAccessBufferSlot::MixerABOut)
#endif

#ifdef UAV_BoneWorldOut
    RWStructuredBuffer<rowMatrix> BoneWorldOut : register(u1);  // (UnorderedAccessBufferSlot::BoneWorldOut)
#endif

// --------------------------------------------------
// bx - b is constant buffer, x - slot
//      in compiled shader its displayed as cbX
//      max count == 15
//      https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/registers---vs-5-0
// --------------------------------------------------

#ifdef CBV_ProjectionMatrix
    cbuffer AA0 : register(b0) // slot 0  (ConstantBufferSlot::vsProjection)
    {
        row_major matrix ProjectionMatrix;
    }
#endif

#ifdef CBV_ViewMatrix
    cbuffer AA1 : register(b1) // slot 1 (ConstantBufferSlot::vsView)
    {
        row_major matrix ViewMatrix;
    }
#endif

#ifdef CBV_WorldMatrix
    cbuffer AA2 : register(b2) // slot 2 (ConstantBufferSlot::vsWorld)
    {
        row_major matrix WorldMatrix; // this is the pivot
    }
#endif

#ifdef CBV_LightColor
    cbuffer AA3 : register(b3) // slot 3 (ConstantBufferSlot::vsLightColor)
    {
        float4 LightColor;
    }
#endif

#ifdef CBV_LightPos
    cbuffer AA4 : register(b4) // slot 4 (ConstantBufferSlot::vsLightPos)
    {
        float4 LightPos;
    }
#endif

#ifdef CBV_UvMatrix
    cbuffer AA3 : register(b5) // slot 5 (ConstantBufferSlot::psUV_Correction)
    {
        row_major matrix UvMatrix;
    }
#endif

#ifdef CBV_InColorX
    cbuffer AA4 : register(b6) // slot 6 (ConstantBufferSlot::psSpriteColor)
    {
        float4 InColorX;
    }
#endif






#ifdef CBV_MixerAB
    cbuffer AA : register(b9) // (ConstantBufferSlot::csMixer)
    {
        float ts;
        uint numBones;
    };
#endif

#ifdef CBV_World
    cbuffer AA : register(b10) // (ConstantBufferSlot::csWorld)
    {
        uint hierarchyDepth;
        uint numBones;
    };
#endif


// --- End of File ---
