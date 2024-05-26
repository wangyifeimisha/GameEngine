//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <d3d11.h>
#include "Engine.h"
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"
#include "DirectXDeviceMan.h"
#include "CameraMan.h"

namespace Azul
{

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_Wireframe::GraphicsObject_Wireframe(Mesh::Name meshName,
													   ShaderObject::Name shaderName, Vec3 &LightColor)
		: GraphicsObject(meshName, shaderName),
		poLightColor(nullptr)

	{
		assert(pMesh);
		assert(pShaderObj);
		assert(poWorld);

		poLightColor = new Vec3(LightColor);
		assert(poLightColor);
	}

	GraphicsObject_Wireframe::~GraphicsObject_Wireframe()
	{
		delete poLightColor;
	}

	void GraphicsObject_Wireframe::SetState()
	{

		// Need to do this properly...
		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;//D3D11_CULL_FRONT;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;

		// To Do add scissor rectangle... its faster
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state object.
		ID3D11RasterizerState *pRasterState;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterState);
		assert(SUCCEEDED(hr));

		DirectXDeviceMan::GetContext()->RSSetState(pRasterState);

		SafeRelease(pRasterState);

	}

	void GraphicsObject_Wireframe::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pMesh->ActivateMesh();

		// w1(7)
		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);
		pMesh->TransferConstantBufferWorldViewProj(pCam, this->poWorld);

		DirectXDeviceMan::GetContext()->UpdateSubresource(pMesh->poConstantBuff_vsLightColor, 0, nullptr, poLightColor, 0, 0);

	}

	void GraphicsObject_Wireframe::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_Wireframe::RestoreState()
	{
		// Need to do this properly...
		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.MultisampleEnable = FALSE;

		// To Do add scissor rectangle... its faster
		rasterizerDesc.ScissorEnable = FALSE;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state object.
		ID3D11RasterizerState *pRasterState;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterState);
		assert(SUCCEEDED(hr));

		DirectXDeviceMan::GetContext()->RSSetState(pRasterState);

		SafeRelease(pRasterState);
	}
}

// ---  End of File ---
