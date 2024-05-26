//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include <d3d11.h>
#include "DLink.h"
#include "MathEngine.h"
#include "Camera.h"
#include "MeshLayout.h"

namespace Azul
{

	class Mesh
	{
	public:

		// needs to match Vertex Shaders
		static const unsigned int BoneCountMax = 8; 

		enum class Name
		{
			CUBE,
			PYRAMID,
			CRATE,
			SPHERE,
			CAMERA,
			SpaceFrigate,
			ChickenBot,
			Bone,
			Bone_001,
			Bone_L,
			Bone_L_001,
			Bone_L_002,
			Bone_R,
			Bone_R_001,
			Bone_R_002,
			SPRITE,
			R2D2,
			Mouse,
			NULL_MESH,
			NOT_INITIALIZED
		};

	public:
		Mesh() = delete;
		Mesh(Mesh &copyMesh) = delete;
		Mesh &operator = (Mesh &copyMesh) = delete;
		virtual ~Mesh();

		Mesh(unsigned int numVerts, unsigned int numTriangles);

		ID3D11Buffer *CreateVertexBuffer(unsigned int NumBytes, void *pData);
		ID3D11Buffer *CreateIndexBuffer(unsigned int NumBytes, void *pData);
		ID3D11Buffer *CreateConstantBuffer(unsigned int NumBytes);

		void Wash();
		bool Compare(DLink *pTarget);
		char *GetName();
		void SetName(Mesh::Name _name);

		void ActivateMesh();
		void TransferConstantBufferWorldViewProj(Camera *pCam, Mat4 *pWorld);

		//void TransferConstantBufferInvBindArray(Mat4 *pInvBindArray);
		//void TransferConstantBufferBoneWorldArray(Mat4 *pWorldBoneArray);

		void RenderIndexBuffer();

		void TransferUVCorrection(Mat4 *pUVMatrix);
		void TransferColor(Vec4 *pColor);

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------

		Name mName;

		unsigned int numVerts;
		unsigned int numIndices;

		// Vertex buffer data
		ID3D11Buffer *poVertexBuffer_pos;
		ID3D11Buffer *poVertexBuffer_color;
		ID3D11Buffer *poVertexBuffer_norm;
		ID3D11Buffer *poVertexBuffer_texCoord;

		// *Skinned Vertex data 
		ID3D11Buffer *poVertexBuffer_weights;
		ID3D11Buffer *poVertexBuffer_joints;

		// Index
		ID3D11Buffer *poIndexBuffer;

		// Shader resources - guaranteed every render
		ID3D11Buffer *poConstantBuff_vsProjection;
		ID3D11Buffer *poConstantBuff_vsWorld;
		ID3D11Buffer *poConstantBuff_vsView;

		// Shader resources - conditional depending on shader
		ID3D11Buffer *poConstantBuff_vsLightColor;
		ID3D11Buffer *poConstantBuff_vsLightPos;

		// for sprite texture
		ID3D11Buffer *poConstantBuff_psUvMatrix;
		ID3D11Buffer *poConstantBuff_psSpriteColor;

		// *Inverse Bind 
		ID3D11Buffer *poConstantBuff_vsInvBind;

		// *BoneWorld
		ID3D11Buffer *poConstantBuff_vsBoneWorld;

		Mat4 *poInvBindArray;

	};
}

#endif

// --- End of File ---
