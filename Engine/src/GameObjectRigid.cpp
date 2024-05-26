//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectRigid.h"
#include "GraphicsObject.h"

namespace Azul
{

	GameObjectRigid::GameObjectRigid(GraphicsObject *pGraphicsObject)
		: GameObject(pGraphicsObject)
	{

	}

	void GameObjectRigid::Update(AnimTime currentTime)
	{

	}

	GameObjectRigid::~GameObjectRigid()
	{
	}

}

// --- End of File ---
