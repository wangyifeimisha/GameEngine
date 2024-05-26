//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectAnimSkeleton.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Anim.h"

namespace Azul
{

	GameObjectAnimSkeleton::GameObjectAnimSkeleton(GraphicsObject *pGraphicsObject, Bone *_pBoneResult)
		: GameObjectAnim(pGraphicsObject)
	{
		assert(pGraphicsObject);
		this->poTrans = new Vec3(0.0f, 0.0f, 0.0f);
		this->poScale = new Vec3(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0.0f, 0.0f, 0.0f, 1.0f);
		this->poLocal = new Mat4(Special::Identity);
		//this->index = -1;

		this->pBoneResult = _pBoneResult;
		assert(_pBoneResult);

		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);
		assert(this->poLocal);
	}

	GameObjectAnimSkeleton::~GameObjectAnimSkeleton()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
		delete this->poLocal;
	
	}

	void GameObjectAnimSkeleton::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		//Trace::out("index: %d \n", index);

		Trans T;
		Scale S;
		Quat  Q;

		// Get the parent matrix... if root, set to identity
		GameObjectAnimSkeleton *pParentObject = (GameObjectAnimSkeleton *)this->GetParent();
		Mat4 matParent(Special::Identity);
		if(pParentObject)
		{
			matParent = *pParentObject->poWorld;

			// REMEMBER this is for Animation and hierachy, 
			//          you need to handle models differently
			// Get the result bone array, from there make the matrix
			T.set(this->pBoneResult[index].T);
			S.set(this->pBoneResult[index].S);
			Q = this->pBoneResult[index].Q;

		}
		else
		{
			T.set(0, 0, 0);
			S.set(1, 1, 1);
			Q.set(Special::Identity);

		}


		// world matrix
		*this->poLocal = S * Q * T;
		*this->poWorld = *poLocal * matParent;

	}

	void GameObjectAnimSkeleton::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

	void GameObjectAnimSkeleton::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectAnimSkeleton::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectAnimSkeleton::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectAnimSkeleton::SetIndex(int i)
	{
		this->index = i;
	}

	void GameObjectAnimSkeleton::SetScale(Vec3 &r)
	{
		*this->poScale = r;
	}

	void GameObjectAnimSkeleton::SetQuat(Quat &r)
	{
		*this->poQuat = r;
	}

	void GameObjectAnimSkeleton::SetTrans(Vec3 &r)
	{
		*this->poTrans = r;
	}


}

// --- End of File ---
