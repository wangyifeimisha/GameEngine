//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_SKIN_FLAT_TEXTURE_H
#define GRAPHICS_OBJECT_SKIN_FLAT_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureObject.h"
#include "Mixer.h"
#include "WorldCompute.h"

namespace Azul
{
	class GraphicsObject_SkinFlatTexture :public GraphicsObject
	{
	public:
		GraphicsObject_SkinFlatTexture(Mesh::Name meshName,
									   ShaderObject::Name shaderName,
									   TextureObject::Name textName,
									   Mixer *pMixer,
									   WorldCompute *pWorldCompute);

		GraphicsObject_SkinFlatTexture() = delete;
		GraphicsObject_SkinFlatTexture(const GraphicsObject_SkinFlatTexture &) = delete;
		GraphicsObject_SkinFlatTexture &operator = (const GraphicsObject_SkinFlatTexture &) = delete;
		virtual ~GraphicsObject_SkinFlatTexture() = default;

		// Render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

	// ---------------------------------------------
	// Data
	// ---------------------------------------------
		TextureObject *pTex;

		// Compute Data
		Mixer *pMixer;
		WorldCompute *pWorldCompute;
	};
}

#endif


// --- End of File ---
