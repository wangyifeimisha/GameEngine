//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_LightTexture.h"
#include "DirectXDeviceMan.h"
#include "CameraMan.h"
#include "TexNodeMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_LightTexture::GraphicsObject_LightTexture(Mesh::Name meshName,
															 ShaderObject::Name shaderName,
															 TextureObject::Name texName,
															 Vec3 &LightColor,
															 Vec3 &LightPos)
		: GraphicsObject(meshName, shaderName),
		pTex(TexNodeMan::Find(texName)),
		poLightColor(nullptr),
		poLightPos(nullptr)
	{
		assert(pTex);

		poLightColor = new Vec3(LightColor);
		poLightPos = new Vec3(LightPos);

		assert(poLightColor);
		assert(poLightPos);
	}

	GraphicsObject_LightTexture::GraphicsObject_LightTexture(Mesh *pMesh,
															 ShaderObject::Name shaderName,
															 TextureObject::Name texName,
															 Vec3 &LightColor,
															 Vec3 &LightPos)
		: GraphicsObject(pMesh->mName, shaderName),
		pTex(TexNodeMan::Find(texName)),
		poLightColor(nullptr),
		poLightPos(nullptr)
	{
		assert(pTex);
		assert(pMesh);

		poLightColor = new Vec3(LightColor);
		poLightPos = new Vec3(LightPos);

		assert(poLightColor);
		assert(poLightPos);
	}

	GraphicsObject_LightTexture::~GraphicsObject_LightTexture()
	{
		delete poLightColor;
		delete poLightPos;
	}

	void GraphicsObject_LightTexture::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		this->pTex->ActivateTexture();
	}

	void GraphicsObject_LightTexture::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		//w1(7)
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);

		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightPos, 0, nullptr, poLightPos, 0, 0);
	}

	void GraphicsObject_LightTexture::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_LightTexture::RestoreState()
	{
		// Future - Undo settings to directX
	}

}

// --- End of File ---
