//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "Sprite.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Anim.h"

namespace Azul
{
	Sprite::Sprite(GraphicsObject *pGraphicsObject)
		: GameObjectRigid(pGraphicsObject),
		scaleX(1.0f),
		scaleY(1.0f),
		posX(0.0f),
		posY(0.0f),
		angle(0.0f)
	{
		assert(pGraphicsObject);
		
		this->pGraphicsObjectSprite = (GraphicsObject_Sprite *)poGraphicsObject;

		this->angle = 0.0f;
		this->posX = pGraphicsObjectSprite->origPosX;
		this->posY = pGraphicsObjectSprite->origPosY;
		this->scaleX = 1.0f;
		this->scaleY = 1.0f;

	}

	Sprite::~Sprite()
	{
		
	}

	void Sprite::SetImage(Image::Name imageName)
	{
		pGraphicsObjectSprite->SetImage(imageName);
	}

	void Sprite::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		Scale S(this->scaleX, this->scaleY, 1.0f);
		Rot R(Rot1::Z, this->angle);
		Trans T(this->posX, this->posY, 0.0f);

		*this->poWorld = S * R * T;
	}

	void Sprite::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}


}

// --- End of File ---
