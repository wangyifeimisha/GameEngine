//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraMesh.h"
#include "CameraMan.h"
#include "Camera.h"
#include "DirectXDeviceMan.h"

namespace Azul
{
	void CameraMesh::update()
	{
		this->privUpdate();
	}

	void CameraMesh::privUpdate()
	{
		// Thrash me - Baby!
		SafeRelease(poVertexBuffer_pos);
		SafeRelease(poVertexBuffer_color);
		SafeRelease(poVertexBuffer_norm);
		SafeRelease(poVertexBuffer_texCoord);

		// skinned
		SafeRelease(poVertexBuffer_weights);
		SafeRelease(poVertexBuffer_joints);

		SafeRelease(poIndexBuffer);

		SafeRelease(poConstantBuff_vsProjection);
		SafeRelease(poConstantBuff_vsWorld);
		SafeRelease(poConstantBuff_vsView);
		SafeRelease(poConstantBuff_vsLightColor);
		SafeRelease(poConstantBuff_vsLightPos);

		SafeRelease(poConstantBuff_vsInvBind);

		VertexPos Vertices_pos[VERT_COUNT];
		VertexNorm Vertices_norm[VERT_COUNT];
		VertexTexCoord Vertices_texCoord[VERT_COUNT];

		// not using this in camera... just a place holder
		VertexWeights Vertices_weights[VERT_COUNT];
		VertexJoints Vertices_joints[VERT_COUNT];

		TriIndex Indices[TRIANGLE_COUNT];

		Vertices_pos[0].Position = Vec3f(-0.000000f, 0.000000f, 0.500000f);
		Vertices_norm[0].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[0].TexCoord = Vec2f(0.000000f, 0.000000f);

		// four triangles
		Indices[0].index = Vec3ui(0, 1, 2);
		Indices[1].index = Vec3ui(0, 2, 3);
		Indices[2].index = Vec3ui(0, 3, 4);
		Indices[3].index = Vec3ui(0, 4, 1);

		// far
		Indices[4].index = Vec3ui(1, 2, 3);
		Indices[5].index = Vec3ui(3, 4, 1);

		// near
		Indices[6].index = Vec3ui(5, 6, 7);
		Indices[7].index = Vec3ui(7, 8, 5);

		Vec3 vTmp;

		Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);
		assert(pCam);
		pCam->updateCamera();

		pCam->getPos(vTmp);

		Vertices_pos[0].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[0].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[0].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarTopRight(vTmp);
		Vertices_pos[1].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[1].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[1].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarTopLeft(vTmp);
		Vertices_pos[2].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[2].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[2].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarBottomLeft(vTmp);
		Vertices_pos[3].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[3].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[3].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarBottomRight(vTmp);
		Vertices_pos[4].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[4].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[4].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearTopRight(vTmp);
		Vertices_pos[5].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[5].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[5].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearTopLeft(vTmp);
		Vertices_pos[6].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[6].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[6].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearBottomLeft(vTmp);
		Vertices_pos[7].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[7].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[7].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearBottomRight(vTmp);
		Vertices_pos[8].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[8].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[8].TexCoord = Vec2f(0.000000f, 0.000000f);

		// Load the verts data: ---------------------------------------------------------

		// Create an initialize the vertex buffer.
		poVertexBuffer_pos = CreateVertexBuffer(sizeof(Vertices_pos), Vertices_pos);
		poVertexBuffer_color = nullptr;
		poVertexBuffer_texCoord = CreateVertexBuffer(sizeof(Vertices_texCoord), Vertices_texCoord);
		poVertexBuffer_norm = CreateVertexBuffer(sizeof(Vertices_norm), Vertices_norm);

		// Additional initialize skinned
		poVertexBuffer_weights = CreateVertexBuffer(sizeof(Vertices_weights), Vertices_weights);
		poVertexBuffer_joints = CreateVertexBuffer(sizeof(Vertices_joints), Vertices_joints);

		// Create and initialize the index buffer.
		poIndexBuffer = CreateIndexBuffer(sizeof(Indices), Indices);

		// Create the constant buffers for the variables defined in the vertex shader.
		poConstantBuff_vsProjection = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_vsView = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_vsWorld = CreateConstantBuffer(sizeof(Mat4));

		// Additional material owned by meshPyramid
		poConstantBuff_vsLightColor = CreateConstantBuffer(sizeof(Vec3));
		poConstantBuff_vsLightPos = CreateConstantBuffer(sizeof(Vec3));

	
	}

	CameraMesh::CameraMesh()
		: Mesh(VERT_COUNT, TRIANGLE_COUNT * 3)
	{

		VertexPos Vertices_pos[VERT_COUNT];
		VertexNorm Vertices_norm[VERT_COUNT];
		VertexTexCoord Vertices_texCoord[VERT_COUNT];

		TriIndex Indices[TRIANGLE_COUNT];

		Vertices_pos[0].Position = Vec3f(-0.000000f, 0.000000f, 0.500000f);
		Vertices_norm[0].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[0].TexCoord = Vec2f(0.000000f, 0.000000f);

		// four triangles
		Indices[0].index = Vec3ui(0, 1, 2);
		Indices[1].index = Vec3ui(0, 2, 3);
		Indices[2].index = Vec3ui(0, 3, 4);
		Indices[3].index = Vec3ui(0, 4, 1);

		// far
		Indices[4].index = Vec3ui(1, 2, 3);
		Indices[5].index = Vec3ui(3, 4, 1);

		// near
		Indices[6].index = Vec3ui(5, 6, 7);
		Indices[7].index = Vec3ui(7, 8, 5);

		Vec3 vTmp;

		Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);
		assert(pCam);
		pCam->updateCamera();

		pCam->getPos(vTmp);

		Vertices_pos[0].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[0].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[0].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarTopRight(vTmp);
		Vertices_pos[1].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[1].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[1].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarTopLeft(vTmp);
		Vertices_pos[2].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[2].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[2].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarBottomLeft(vTmp);
		Vertices_pos[3].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[3].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[3].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getFarBottomRight(vTmp);
		Vertices_pos[4].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[4].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[4].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearTopRight(vTmp);
		Vertices_pos[5].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[5].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[5].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearTopLeft(vTmp);
		Vertices_pos[6].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[6].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[6].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearBottomLeft(vTmp);
		Vertices_pos[7].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[7].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[7].TexCoord = Vec2f(0.000000f, 0.000000f);

		pCam->getNearBottomRight(vTmp);
		Vertices_pos[8].Position = Vec3f(vTmp[x], vTmp[y], vTmp[z]);
		Vertices_norm[8].Norm = Vec3f(0.000000f, 0.000000f, 0.000000f);
		Vertices_texCoord[8].TexCoord = Vec2f(0.000000f, 0.000000f);

		// Load the verts data: ---------------------------------------------------------

		// Create an initialize the vertex buffer.
		poVertexBuffer_pos = CreateVertexBuffer(sizeof(Vertices_pos), Vertices_pos);
		poVertexBuffer_color = nullptr;
		poVertexBuffer_texCoord = CreateVertexBuffer(sizeof(Vertices_texCoord), Vertices_texCoord);
		poVertexBuffer_norm = CreateVertexBuffer(sizeof(Vertices_norm), Vertices_norm);

		// Create and initialize the index buffer.
		poIndexBuffer = CreateIndexBuffer(sizeof(Indices), &Indices[0]);

		// Create the constant buffers for the variables defined in the vertex shader.
		poConstantBuff_vsProjection = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_vsView = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_vsWorld = CreateConstantBuffer(sizeof(Mat4));

		// Additional material owned by meshPyramid
		poConstantBuff_vsLightColor = CreateConstantBuffer(sizeof(Vec3));
		poConstantBuff_vsLightPos = CreateConstantBuffer(sizeof(Vec3));
	}


	CameraMesh::~CameraMesh()
	{
		// remove anything dynamic here
	}

}

// --- End of File ---
