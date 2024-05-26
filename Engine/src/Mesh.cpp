//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Engine.h"
#include "Mesh.h"
#include "ShaderMappings.h"

#include "StringThis.h"

#include "DirectXDeviceMan.h"

namespace Azul
{
	Mesh::Mesh(unsigned int _numVerts, unsigned int _numIndices)
		:
		numVerts{_numVerts},
		numIndices{_numIndices},
		poVertexBuffer_pos{nullptr},
		poVertexBuffer_color{nullptr},
		poVertexBuffer_norm{nullptr},
		poVertexBuffer_texCoord{nullptr},

		poVertexBuffer_weights{nullptr},
		poVertexBuffer_joints{nullptr},

		poIndexBuffer{nullptr},
		poConstantBuff_vsProjection{nullptr},
		poConstantBuff_vsWorld{nullptr},
		poConstantBuff_vsView{nullptr},
		poConstantBuff_vsLightColor{nullptr},
		poConstantBuff_vsLightPos{nullptr},

		poConstantBuff_psUvMatrix{nullptr},
		poConstantBuff_psSpriteColor{nullptr},

		poConstantBuff_vsInvBind{nullptr},
		poConstantBuff_vsBoneWorld{nullptr},
		
		poInvBindArray{new Mat4[BoneCountMax]()}
	{
		assert(poInvBindArray);
		for(size_t i = 0; i < BoneCountMax; i++)
		{
			poInvBindArray[i].set(Special::Identity);
		}
	}

	Mesh::~Mesh()
	{
		SafeRelease(poVertexBuffer_pos);
		SafeRelease(poVertexBuffer_color);
		SafeRelease(poVertexBuffer_norm);
		SafeRelease(poVertexBuffer_texCoord);

		SafeRelease(poVertexBuffer_weights);
		SafeRelease(poVertexBuffer_joints);

		SafeRelease(poIndexBuffer);
		SafeRelease(poConstantBuff_vsProjection);
		SafeRelease(poConstantBuff_vsWorld);
		SafeRelease(poConstantBuff_vsView);
		SafeRelease(poConstantBuff_vsLightColor);
		SafeRelease(poConstantBuff_vsLightPos);

		SafeRelease(poConstantBuff_psUvMatrix);
		SafeRelease(poConstantBuff_psSpriteColor);

		SafeRelease(poConstantBuff_vsInvBind);
		SafeRelease(poConstantBuff_vsBoneWorld);

		delete[] poInvBindArray;
		poInvBindArray = nullptr;
	}


	void Mesh::Wash()
	{

	}

	bool Mesh::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Mesh *pDataB = (Mesh *)pTarget;

		bool status = false;

		if(this->mName == pDataB->mName)
		{
			status = true;
		}

		return status;
	}

	void Mesh::SetName(Mesh::Name _name)
	{
		this->mName = _name;
	}

	char *Mesh::GetName()
	{
		// todo - Hack understand why is this needed for print and fix...
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->mName));
		return pTmp;
	}


	void Mesh::RenderIndexBuffer()
	{
		// ---------------------------------------------
		//    Set (point to ) Index buffer 
		//    Render configuration: Triangles
		// ---------------------------------------------
		DirectXDeviceMan::GetContext()->IASetIndexBuffer(poIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		DirectXDeviceMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//--------------------------------------------------------
		// RENDER - using index data
		//--------------------------------------------------------
		DirectXDeviceMan::GetContext()->DrawIndexed(numIndices, 0, 0);
	}

	void Mesh::TransferConstantBufferWorldViewProj(Camera *pCam, Mat4 *pWorld)
	{
		assert(pCam);
		assert(pWorld);

		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_vsView, 
														  0, nullptr, &pCam->getViewMatrix(), 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_vsProjection, 
														  0, nullptr, &pCam->getProjMatrix(), 0, 0);
		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_vsWorld, 
														  0, nullptr, pWorld, 0, 0);
	}

	//void Mesh::TransferConstantBufferInvBindArray(Mat4 *pInvBindArray)
	//{
	//	assert(pInvBindArray);
	//	DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_vsInvBind, 
	//													  0, 
	//													  nullptr, 
	//													  pInvBindArray, 
	//													  0, 
	//													  0);
	//}

	//void Mesh::TransferConstantBufferBoneWorldArray(Mat4 *pBoneWorldArray)
	//{
	//	assert(pBoneWorldArray);
	//	DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_vsBoneWorld,
	//													  0,
	//													  nullptr,
	//													  pBoneWorldArray,
	//													  0,
	//													  0);
	//}

	void Mesh::TransferUVCorrection(Mat4 *pUVMatrix)
	{
		assert(pUVMatrix);
		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_psUvMatrix, 0, nullptr, pUVMatrix, 0, 0);
	}

	void Mesh::TransferColor(Vec4 *pColor)
	{
		assert(pColor);
		DirectXDeviceMan::GetContext()->UpdateSubresource(poConstantBuff_psSpriteColor, 0, nullptr, pColor, 0, 0);
	}

	void Mesh::ActivateMesh()
	{

		// ---------------------------------------------
		//    Set (point to ) vertex: position 
		//    Set (point to ) vertex: color
		// ---------------------------------------------
		const UINT offset = 0;

		if(poVertexBuffer_pos)
		{
			const UINT vertexStride_pos = sizeof(VertexPos);
			DirectXDeviceMan::GetContext()->IASetVertexBuffers((uint32_t)VertexSlot::Position, 1, &poVertexBuffer_pos, &vertexStride_pos, &offset);
		}

		if(poVertexBuffer_color)
		{
			const UINT vertexStride_color = sizeof(VertexColor);
			DirectXDeviceMan::GetContext()->IASetVertexBuffers((uint32_t)VertexSlot::Color, 1, &poVertexBuffer_color, &vertexStride_color, &offset);
		}

		if(poVertexBuffer_norm)
		{
			const UINT vertexStride_norm = sizeof(VertexNorm);
			DirectXDeviceMan::GetContext()->IASetVertexBuffers((uint32_t)VertexSlot::Norm, 1, &poVertexBuffer_norm, &vertexStride_norm, &offset);
		}

		if(poVertexBuffer_texCoord)
		{
			const UINT vertexStride_texCoord = sizeof(VertexTexCoord);
			DirectXDeviceMan::GetContext()->IASetVertexBuffers((uint32_t)VertexSlot::TexCoord, 1, &poVertexBuffer_texCoord, &vertexStride_texCoord, &offset);
		}

		if(poVertexBuffer_weights)
		{
			const UINT vertexStride_weights = sizeof(VertexWeights);
			DirectXDeviceMan::GetContext()->IASetVertexBuffers((uint32_t)VertexSlot::Weights, 1, &poVertexBuffer_weights, &vertexStride_weights, &offset);
		}

		if(poVertexBuffer_joints)
		{
			const UINT vertexStride_joints = sizeof(VertexJoints);
			DirectXDeviceMan::GetContext()->IASetVertexBuffers((uint32_t)VertexSlot::Joints, 1, &poVertexBuffer_joints, &vertexStride_joints, &offset);
		}

		//--------------------------------------------------
		// Enable shader
		//    Set (point to the shader to use)
		//    Set (point to the constant buffers to use)
		//--------------------------------------------------
		DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsProjection, 1, &poConstantBuff_vsProjection);
		DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsView, 1, &poConstantBuff_vsView);
		DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsWorld, 1, &poConstantBuff_vsWorld);

		if(poConstantBuff_vsInvBind)
		{
			DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsInvBind,
																 1,
																 &poConstantBuff_vsInvBind);
		}

		if(poConstantBuff_vsBoneWorld)
		{
			DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsBoneWorld, 
																 1, 
																 &poConstantBuff_vsBoneWorld);
		}

		if(poConstantBuff_vsLightColor)
		{
			DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsLightColor,
																 1,
																 &poConstantBuff_vsLightColor);
		}

		if(poConstantBuff_vsLightPos)
		{
			DirectXDeviceMan::GetContext()->VSSetConstantBuffers((uint32_t)ConstantBufferSlot::vsLightPos,
																 1,
																 &poConstantBuff_vsLightPos);
		}

		if(poConstantBuff_psUvMatrix)
		{
			DirectXDeviceMan::GetContext()->PSSetConstantBuffers((uint32_t)ConstantBufferSlot::psUV_Correction,
																 1,
																 &poConstantBuff_psUvMatrix);
		}


		if(poConstantBuff_psSpriteColor)
		{
			// HEY dumbass - there is a PS and a VS set constant
			DirectXDeviceMan::GetContext()->PSSetConstantBuffers((uint32_t)ConstantBufferSlot::psSpriteColor,
																 1,
																 &poConstantBuff_psSpriteColor);
		}

	}

	ID3D11Buffer *Mesh::CreateVertexBuffer(unsigned int NumBytes, void *pData)
	{
		assert(pData);

		// Create an initialize the vertex buffer.
		D3D11_BUFFER_DESC vertexBufferDesc{0};
		D3D11_SUBRESOURCE_DATA resourceData{0};

		// type of buffer
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.ByteWidth = NumBytes;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		resourceData.pSysMem = pData;
		ID3D11Buffer *pVertexBuffer;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&vertexBufferDesc, &resourceData, &pVertexBuffer);
		assert(SUCCEEDED(hr));

		return pVertexBuffer;
	}

	ID3D11Buffer *Mesh::CreateIndexBuffer(unsigned int NumBytes, void *pData)
	{
		assert(pData);

		// Create and initialize the index buffer.
		D3D11_BUFFER_DESC indexBufferDesc{0};
		D3D11_SUBRESOURCE_DATA resourceData{0};

		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.ByteWidth = NumBytes;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		resourceData.pSysMem = pData;

		ID3D11Buffer *pIndexBuffer;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&indexBufferDesc, &resourceData, &pIndexBuffer);
		assert(SUCCEEDED(hr));

		return pIndexBuffer;
	}

	ID3D11Buffer *Mesh::CreateConstantBuffer(unsigned int NumBytes)
	{

		D3D11_BUFFER_DESC constantBufferDesc{0};

		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.ByteWidth = NumBytes;
		constantBufferDesc.CPUAccessFlags = 0;
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		ID3D11Buffer *pConstantBuffer;
		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, &pConstantBuffer);
		assert(SUCCEEDED(hr));

		return pConstantBuffer;
	}
}

// --- End of File ---
