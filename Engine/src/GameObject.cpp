//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"
#include "GraphicsObject.h"
#include "Mesh.h"

namespace Azul
{

	GameObject::GameObject(GraphicsObject *pGraphicsObject)
		: poGraphicsObject(pGraphicsObject),
		mDrawEnable(true)
	{
		this->poWorld = new Mat4(Special::Identity);
		assert(poWorld);

		assert(pGraphicsObject);
	}

	GameObject::~GameObject()
	{
		delete this->poWorld;
		delete this->poGraphicsObject;
	}

	Mat4 *GameObject::GetWorld()
	{
		return this->poWorld;
	}

	GraphicsObject *GameObject::GetGraphicsObject()
	{
		return this->poGraphicsObject;
	}

	void GameObject::SetWorld(Mat4 *pWorld)
	{
		assert(pWorld);
		*this->poWorld = *pWorld;
	}

	void GameObject::DrawEnable()
	{
		this->mDrawEnable = true;
	}

	void GameObject::DrawDisable()
	{
		this->mDrawEnable = false;
	}

	void GameObject::Draw()
	{
		GraphicsObject *pGraphicsObj = this->GetGraphicsObject();
		assert(pGraphicsObj);

		if(this->mDrawEnable)
		{
			pGraphicsObj->Render();
		}
	}

}

// --- End of File ---
