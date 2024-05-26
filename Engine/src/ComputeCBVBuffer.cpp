//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ComputeCBVBuffer.h"
#include "DirectXDeviceMan.h"

namespace Azul
{
	ComputeCBVBuffer::ComputeCBVBuffer( size_t _structSize)
		: structSize{_structSize},
		pBuff{nullptr},
		poComputeCBVBuffer{nullptr},
		bCreate{false}
	{
		this->privCreate(_structSize);
	}

	void ComputeCBVBuffer::privCreate(size_t _structSize)
	{
		// in case set was called before
		assert(this->bCreate == false);
		this->bCreate = true;

		this->structSize = _structSize;
		assert(structSize > 0);

		D3D11_BUFFER_DESC BufferDesc{0};

		//  shader resource
		BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.ByteWidth = this->structSize;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;

		HRESULT hr;
		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&BufferDesc, 
														 nullptr, 
														 &this->poComputeCBVBuffer);
		assert(SUCCEEDED(hr));
	}

	void ComputeCBVBuffer::Transfer(void *_pBuff)
	{
		// in case set was called before
		assert(this->bCreate == true);

		this->pBuff = _pBuff;
		assert(pBuff);

		DirectXDeviceMan::GetContext()->UpdateSubresource(poComputeCBVBuffer,
														  0,
														  nullptr,
														  pBuff,
														  0,
														  0);
	}

	void ComputeCBVBuffer::BindCompute(ConstantBufferSlot slot)
	{

		DirectXDeviceMan::GetContext()->CSSetConstantBuffers((uint32_t)slot,
															 1,
															 &this->poComputeCBVBuffer);

	}

	ComputeCBVBuffer::~ComputeCBVBuffer()
	{
		SafeRelease(this->poComputeCBVBuffer);
	}

}

//--- End of File ---
