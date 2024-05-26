//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMPUTE_CBV_BUFFER_H
#define COMPUTE_CBV_BUFFER_H

#include <d3d11.h>
#include "ShaderMappings.h"

namespace Azul
{
	class ComputeCBVBuffer
	{
	public:
		ComputeCBVBuffer() = delete;
		ComputeCBVBuffer(const ComputeCBVBuffer &r) = delete;
		ComputeCBVBuffer &operator=(const ComputeCBVBuffer &) = delete;
		virtual ~ComputeCBVBuffer();

		ComputeCBVBuffer(size_t structSize);

		void Transfer(void *pBuff);
		void BindCompute(ConstantBufferSlot slot);

	private:
		void privCreate( size_t structSize);

	// ----------------------
	//  Data
	// -----------------------
	public:
		size_t structSize;
		void *pBuff;
		ID3D11Buffer *poComputeCBVBuffer;
		bool bCreate;
	};
}

#endif

//--- End of File ---
