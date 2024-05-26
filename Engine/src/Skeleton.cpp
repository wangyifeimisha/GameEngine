//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject_LightTexture.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_SkinFlatTexture.h"
#include "GameObjectBasic.h"
#include "GameObjectMan.h"
#include "ShaderObjectNodeMan.h"
#include "GameObjectRigid.h"
#include "GraphicsObject_Null.h"
#include "Skeleton.h"
#include "MeshNodeMan.h"
#include "GameObjectAnimSkeleton.h"
#include "GameObjectAnimSkin.h"
#include "TexNodeMan.h"
#include "PCSTreeForwardIterator.h"
#include "SkelMan.h"

namespace Azul
{
	Skeleton::Skeleton(Clip *pClip, ComputeUAVBuffer *pBone)
		: pFirstBone(nullptr),
		numBones(pClip->GetNumBones())
	{
		assert(pBone);
		assert(pClip);
		this->privSetAnimationHierarchy(pBone, pClip->GetSkelName());
		assert(pFirstBone);
	}

	Skeleton::~Skeleton()
	{

	}

	GameObjectAnim *Skeleton::GetFirstBone()
	{
		assert(pFirstBone);
		return this->pFirstBone;
	}

	GameObjectAnim *Skeleton::FindBoneByIndex(int index)
	{
		GameObjectAnim *pFound = nullptr;

		GameObjectAnim *pObj = this->GetFirstBone();

		// TODO - add test bed for an interator of a tree with only one node
		if(pObj->index == index)
		{
			pFound = pObj;
		}
		else
		{
			PCSTreeForwardIterator pIter(pObj);
			PCSNode *pNode = pIter.First();
			GameObjectAnim *pGameObj = nullptr;

			// walks the anim node does the pose for everything that
			while(pNode != nullptr)
			{
				assert(pNode);
				// Update the game object
				pGameObj = (GameObjectAnim *)pNode;
				if(pGameObj->index == index)
				{
					pFound = pGameObj;
					break;
				}
				pNode = pIter.Next();
			}
		}

		return pFound;
	}

	void Skeleton::privSetAnimationHierarchy(ComputeUAVBuffer *pBoneResult, Skel::Name skelName)
	{
		AZUL_UNUSED_VAR(pBoneResult);
		AZUL_UNUSED_VAR(skelName);
		assert(pBoneResult);
		assert(skelName);

		////---------------------------------------
		//// ChickenBot
		////---------------------------------------

		//Skel *pSkel = SkelMan::Find(skelName);
		//assert(pSkel);

		//// GraphicsObject for a specific instance
		//GraphicsObject *pGraphicsObj;

		//// Animation
		//GameObjectAnim *pGameObj;

		//// Root animation is treated differently
		//for(int i = 0; i < 1; i++)
		//{
		//	pGraphicsObj = new GraphicsObject_Null(Mesh::Name::NULL_MESH, ShaderObject::Name::NullShader);
		//	pGameObj = new GameObjectAnimSkeleton(pGraphicsObj, pBoneResult);
		//	pGameObj->SetIndex(pSkel->poTableArray[i].index);
		//	pGameObj->SetName(pSkel->poTableArray[i].name);

		//	GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		//	this->pFirstBone = pGameObj;
		//}

		//for(int i = 1; i < this->numBones; i++)
		//{
		//	pGraphicsObj = new GraphicsObject_Null(Mesh::Name::NULL_MESH, ShaderObject::Name::NullShader);
		//	pGameObj = new GameObjectAnimSkeleton(pGraphicsObj, pBoneResult);
		//	pGameObj->SetIndex(pSkel->poTableArray[i].index);
		//	pGameObj->SetName(pSkel->poTableArray[i].name);

		//	GameObjectAnim *pParent = this->FindBoneByIndex(pSkel->poTableArray[i].parentIndex);
		//	assert(pParent);
		//	GameObjectMan::Add(pGameObj, pParent);
		//}
	}


	int Skeleton::GetNumBones() const
	{
		return this->numBones;
	}
}

// --- End of File ---
