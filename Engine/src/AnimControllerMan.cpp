//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimControllerMan.h"
#include "DLinkMan.h"

namespace Azul
{

    AnimControllerMan* AnimControllerMan::posInstance = nullptr;

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    AnimControllerMan::AnimControllerMan(int reserveNum, int reserveGrow)
        : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
    {
        // Preload the reserve
        this->proFillReservedPool(reserveNum);

        // initialize derived data here
        //this->poNodeCompare = new AnimController();
        this->poNodeCompare = nullptr;
    }

    AnimControllerMan::~AnimControllerMan()
    {
        delete this->poNodeCompare;
        this->poNodeCompare = nullptr;

        // iterate through the list and delete
        Iterator* pIt = this->baseGetActiveIterator();

        DLink* pNode = pIt->First();

        // Walk through the nodes
        while (!pIt->IsDone())
        {
            AnimController* pDeleteMe = (AnimController*)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }

        pIt = this->baseGetReserveIterator();

        pNode = pIt->First();

        // Walk through the nodes
        while (!pIt->IsDone())
        {
            AnimController* pDeleteMe = (AnimController*)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }
    }

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
    void AnimControllerMan::Create(int reserveNum, int reserveGrow)
    {
        // make sure values are ressonable 
        assert(reserveNum >= 0);
        assert(reserveGrow > 0);

        // initialize the singleton here
        assert(posInstance == nullptr);

        // Do the initialization
        if (posInstance == nullptr)
        {
            posInstance = new AnimControllerMan(reserveNum, reserveGrow);
        }

    }

    void AnimControllerMan::Destroy()
    {
        AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
        assert(pMan != nullptr);
        AZUL_UNUSED_VAR(pMan);

        delete AnimControllerMan::posInstance;
        AnimControllerMan::posInstance = nullptr;
    }

    void AnimControllerMan::Add(AnimController* pAnimController)
    {
        
        AnimControllerMan* pMan = AnimControllerMan::privGetInstance();

        AnimController* pNode = (AnimController*)pMan->baseAddToFront();
        assert(pNode != nullptr);
    }

    void AnimControllerMan::Remove(AnimController* pNode)
    {
        assert(pNode != nullptr);

        AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseRemove(pNode);
    }

    void AnimControllerMan::Dump()
    {
        AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseDump();
    }

    void AnimControllerMan::Update()
    {
        // iterate through the list and delete
        Iterator* pIt = this->baseGetActiveIterator();

        DLink* pNode = pIt->First();

        // Walk through the nodes
        while (!pIt->IsDone())
        {
            AnimController* pAC = (AnimController*)pIt->Curr();
            pAC->Update();
            pNode = pIt->Next();
          
        }
    }

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
    AnimControllerMan* AnimControllerMan::privGetInstance()
    {
        // Safety - this forces users to call Create() first before using class
        assert(posInstance != nullptr);

        return posInstance;
    }

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
    DLink* AnimControllerMan::derivedCreateNode()
    {
        //DLink* pNodeBase = new AnimController();
        //assert(pNodeBase != nullptr);
        //
        return nullptr;
    }
}

// --- End of File ---
