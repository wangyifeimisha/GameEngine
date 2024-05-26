//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_SPRITE_H
#define GAME_OBJECT_SPRITE_H

#include "GameObjectRigid.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"
#include "Image.h"
#include "GraphicsObject_Sprite.h"

namespace Azul
{
	class Sprite : public GameObjectRigid
	{
	public:
		Sprite(GraphicsObject *graphicsObject);

		// Big four
		Sprite() = delete;
		Sprite(const Sprite &) = delete;
		Sprite &operator=(Sprite &) = delete;
		virtual ~Sprite() override;

		void SetImage(Image::Name image);

		virtual void Update(AnimTime currTime);

	private:
		void privUpdate(AnimTime currTime);

	public:   // add accessors later
		float scaleX;
		float scaleY;
		float posX;
		float posY;
		float angle;

		// alias
		GraphicsObject_Sprite *pGraphicsObjectSprite;

	};
}

#endif

// --- End of File ---
