//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMPUTE_UAV_BUFFER_H
#define COMPUTE_UAV_BUFFER_H

#include <d3d11.h>
#include "ShaderMappings.h"

namespace Azul
{
	struct BufType
	{
		int i;
		float f;
	};

	class ComputeUAVBuffer
	{
	public:
		ComputeUAVBuffer() = delete;
		ComputeUAVBuffer(const ComputeUAVBuffer &r) = delete;
		ComputeUAVBuffer &operator=(const ComputeUAVBuffer &) = delete;
		virtual ~ComputeUAVBuffer();

		ComputeUAVBuffer(size_t count, size_t structSize);

		void Transfer(void *pBuff);
		void BindCompute(UnorderedAccessBufferSlot slot);

	private:
		void privCreate(size_t count, size_t structSize);

		// ----------------------
		//  Data
		// -----------------------
	public:
		size_t count;
		size_t structSize;
		void *pBuff;
		ID3D11Buffer *poComputeUAVBuffer;
		ID3D11UnorderedAccessView *poUnorderedAccessView;
		bool bCreate;
	};
}

#endif

//--- End of File ---
