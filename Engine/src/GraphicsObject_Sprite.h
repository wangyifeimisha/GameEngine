//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_SPRITE_H
#define GRAPHICS_OBJECT_SPRITE_H

#include "GraphicsObject.h"
#include "TextureObject.h"
#include "Image.h"
#include "Rect.h"
#include "Color.h"

namespace Azul
{
	class GraphicsObject_Sprite :public GraphicsObject
	{
	public:
		GraphicsObject_Sprite(Mesh::Name meshName, 
							  ShaderObject::Name shaderName, 
							  Image::Name imageName, 
							  Rect rect);

		GraphicsObject_Sprite() = delete;
		GraphicsObject_Sprite(const GraphicsObject_Sprite &) = delete;
		GraphicsObject_Sprite &operator = (const GraphicsObject_Sprite &) = delete;
		virtual ~GraphicsObject_Sprite();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here

		void SetImage(Image::Name image);
		void SetTexture(TextureObject *pText);
		void SetImage(Rect &imageRect, TextureObject *pText);
		void SetScreenRect(Rect &rect);

		// w1(7)
		Image *pImage;
		TextureObject *pTexture;
		Mat4 *poMatrix_uv;
		Mat4 *poMatrix_orig;
		Color color;

		float origWidth;
		float origHeight;

		float origPosX;
		float origPosY;
	};
}

#endif


// --- End of File ---
