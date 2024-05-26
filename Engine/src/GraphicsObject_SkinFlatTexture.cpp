//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_SkinFlatTexture.h"
#include "CameraMan.h"
#include "GameMan.h"
#include "TexNodeMan.h"
#include "DirectXDeviceMan.h"
#include "ComputeRSVBuffer.h"
#include "ShaderMappings.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_SkinFlatTexture::GraphicsObject_SkinFlatTexture(Mesh::Name meshName,
																   ShaderObject::Name shaderName,
																   TextureObject::Name textName,
																   Mixer *_pMixer,
																   WorldCompute *_pWorldCompute)
		: GraphicsObject(meshName, shaderName),
		pTex{nullptr},
		pMixer{_pMixer},
		pWorldCompute{_pWorldCompute}
	{
		this->pTex = TexNodeMan::Find(textName);
		assert(pTex);
		assert(pMixer);
		assert(pWorldCompute);
	}

	void GraphicsObject_SkinFlatTexture::SetState()
	{
		// Future - settings to directX
		// say make it wireframe or change culling mode
		this->pTex->ActivateTexture();
	}

	void GraphicsObject_SkinFlatTexture::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);

		// Set the InvBind to Vertex shader
		assert(pWorldCompute->poVsInvBind);
		pWorldCompute->poVsInvBind->BindVertex(ShaderResourceBufferSlot::InvBind);

		// Set the BoneWorld to Vertex shader
		assert(pWorldCompute->poVsBoneWorld);
		pWorldCompute->poVsBoneWorld->BindVertex(ShaderResourceBufferSlot::BoneWorldIn);
	}

	void GraphicsObject_SkinFlatTexture::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_SkinFlatTexture::RestoreState()
	{
		Game *pGame = GameMan::GetGame();
		float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		UINT sampleMask = 0xffffffff;
		pGame->g_d3dDeviceContext->OMSetBlendState(pGame->g_d3eBlendStateOff, blendFactor, sampleMask);
	}

}

// --- End of File ---
