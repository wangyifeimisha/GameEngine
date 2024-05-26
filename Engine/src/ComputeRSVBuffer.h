//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMPUTE_RSV_BUFFER_H
#define COMPUTE_RSV_BUFFER_H

#include <d3d11.h>

#include "ShaderMappings.h"

namespace Azul
{
	class ComputeRSVBuffer
	{
	public:
		ComputeRSVBuffer() = delete;
		ComputeRSVBuffer(const ComputeRSVBuffer &r) = delete;
		ComputeRSVBuffer &operator=(const ComputeRSVBuffer &) = delete;
		virtual ~ComputeRSVBuffer();

		ComputeRSVBuffer(size_t count, size_t structSize);


		void Transfer(void *pBuff);
		void BindCompute(ShaderResourceBufferSlot slot);
		void BindVertex(ShaderResourceBufferSlot slot);

	private:
		void privCreate(size_t count, size_t structSize);

	// ----------------------
	//  Data
	// -----------------------
	public:
		size_t count;
		size_t structSize;
		void *pBuff;
		ID3D11Buffer *poComputeRVSBuffer;
		ID3D11ShaderResourceView *poShaderResourceView;
		bool bCreate;
	};
}

#endif

//--- End of File ---
