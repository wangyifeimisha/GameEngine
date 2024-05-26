//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MeshNull.h"
#include "GraphicsObject_Null.h"
#include "ShaderObject_Null.h"
#include "GameObject.h"
#include "GameObjectRigid.h"
#include "GameObjectMan.h"
#include "PCSTreeForwardIterator.h"
#include "MeshNodeMan.h"
#include "ShaderObjectNodeMan.h"

namespace Azul
{
	void GameObjectMan::Add(GameObject *pObj, GameObject *pParent)
	{
		assert(pObj);
		assert(pParent);

		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();

		// insert object to root
		pGOM->poRootTree->Insert(pObj, pParent);
	}

	PCSTree *GameObjectMan::GetPCSTree()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		return pGOM->poRootTree;
	}

	GameObject *GameObjectMan::GetRoot()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		GameObject *pGameObj = (GameObject *)pGOM->poRootTree->GetRoot();
		assert(pGameObj);

		return pGameObj;
	}

	void GameObjectMan::Create()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);
		AZUL_UNUSED_VAR(pGOM);
	}

	void GameObjectMan::Destroy()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSTree *pTree = pGOM->poRootTree;
		PCSNode *pNode = nullptr;

		PCSTreeForwardIterator pForIter(pTree->GetRoot());
		pNode = pForIter.First();
		PCSNode *pTmp = nullptr;

		// todo: create an Erase() like SE456
		while(!pForIter.IsDone())
		{
			pTmp = pForIter.Current();

			pNode = pForIter.Next();
			delete pTmp;
		}
	}

	void GameObjectMan::Update(AnimTime currentTime)
	{
		//Trace::out("\n");
		//Trace::out("------ GameObjectMan::Update() -----------------\n");
		//Trace::out("\n");

		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pIt(pRootNode);

		GameObject *pGameObj = nullptr;

		for(pIt.First(); !pIt.IsDone(); pIt.Next())
		{
			pGameObj = (GameObject *)pIt.Current();
		//	pGameObj->PrintNode();
			pGameObj->Update(currentTime);
		}
	}

	void GameObjectMan::Draw()
	{
		//	Trace::out("\n");
		//	Trace::out("--- GameObjectMan::Draw() ----\n");
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pIt(pRootNode);

		GameObject *pGameObj = nullptr;

		for(pIt.First(); !pIt.IsDone(); pIt.Next())
		{
			pGameObj = (GameObject *)pIt.Current();
				//pGameObj->PrintNode();
			pGameObj->Draw();
		}
	}

	GameObjectMan::GameObjectMan()
	{
		// Create the root node (null object)
		MeshNull *pMesh = new MeshNull();
		assert(pMesh);

		MeshNodeMan::Add(Mesh::Name::NULL_MESH, pMesh);

		ShaderObject *pShader = new ShaderObject_Null(ShaderObject::Name::NullShader);
		assert(pShader);
		ShaderObjectNodeMan::Add(pShader);

		GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(Mesh::Name::NULL_MESH, ShaderObject::Name::NullShader);
		GameObjectRigid *pGameRoot = new GameObjectRigid(pGraphicsObject);
		pGameRoot->SetName("GameObject_Root");

		// Create the tree
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		// Attach the root node
		this->poRootTree->Insert(pGameRoot, this->poRootTree->GetRoot());
	}

	GameObjectMan::~GameObjectMan()
	{
		delete this->poRootTree;
	}

	GameObjectMan *GameObjectMan::privGetInstance(void)
	{
		// This is where its actually stored (BSS section)
		static GameObjectMan gom;
		return &gom;
	}

}

// --- End of File ---
