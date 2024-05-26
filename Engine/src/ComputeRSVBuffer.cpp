//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ComputeRSVBuffer.h"
#include "DirectXDeviceMan.h"

namespace Azul
{
	ComputeRSVBuffer::ComputeRSVBuffer(size_t _count, size_t _structSize)
		: count{_count},
		structSize{_structSize},
		pBuff{nullptr},
		poComputeRVSBuffer{nullptr},
		poShaderResourceView{nullptr},
		bCreate{false}
	{
		this->privCreate(_count, _structSize);
	}

	void ComputeRSVBuffer::privCreate(size_t _count, size_t _structSize)
	{
		// in case set was called before
		assert(this->bCreate == false);
		this->bCreate = true;

		this->count = _count;
		this->structSize = _structSize;

		assert(count > 0);
		assert(structSize > 0);

		D3D11_BUFFER_DESC BufferDesc{0};

		//  shader resource
		BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		BufferDesc.ByteWidth = this->count * this->structSize;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		BufferDesc.StructureByteStride = this->structSize;

		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&BufferDesc, 
														 nullptr, 
														 &this->poComputeRVSBuffer);
		assert(SUCCEEDED(hr));

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvDesc.BufferEx.FirstElement = 0;
		srvDesc.BufferEx.Flags = 0;
		srvDesc.BufferEx.NumElements = this->count;    // number of structures

		hr = DirectXDeviceMan::GetDevice()->CreateShaderResourceView(poComputeRVSBuffer, &srvDesc, &this->poShaderResourceView);
		assert(SUCCEEDED(hr));
	}

	void ComputeRSVBuffer::Transfer(void *_pBuff)
	{
		// in case set was called before
		assert(this->bCreate == true);

		this->pBuff = _pBuff;
		assert(pBuff);

		DirectXDeviceMan::GetContext()->UpdateSubresource(poComputeRVSBuffer,
														  0,
														  nullptr,
														  pBuff,
														  0,
														  0);
	}

	void ComputeRSVBuffer::BindCompute(ShaderResourceBufferSlot slot)
	{

		DirectXDeviceMan::GetContext()->CSSetShaderResources((size_t)slot,
															 1,
															 &this->poShaderResourceView);

	}

	void ComputeRSVBuffer::BindVertex(ShaderResourceBufferSlot slot)
	{

		DirectXDeviceMan::GetContext()->VSSetShaderResources((size_t)slot,
															 1,
															 &this->poShaderResourceView);

	}

	ComputeRSVBuffer::~ComputeRSVBuffer()
	{
		SafeRelease(this->poComputeRVSBuffer);
		SafeRelease(this->poShaderResourceView);
	}

}

//--- End of File ---
