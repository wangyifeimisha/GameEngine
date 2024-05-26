//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "InvBindMan.h"
#include "DLinkMan.h"
#include "InvBindProto.h"

namespace Azul
{

    InvBindMan *InvBindMan::posInstance = nullptr;

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    InvBindMan::InvBindMan(int reserveNum, int reserveGrow)
        : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
    {
        // Preload the reserve
        this->proFillReservedPool(reserveNum);

        // initialize derived data here
        this->poNodeCompare = new InvBind();
    }

    InvBindMan::~InvBindMan()
    {
        delete this->poNodeCompare;
        this->poNodeCompare = nullptr;

        // iterate through the list and delete
        Iterator *pIt = this->baseGetActiveIterator();

        DLink *pNode = pIt->First();

        // Walk through the nodes
        while(!pIt->IsDone())
        {
            InvBind *pDeleteMe = (InvBind *)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }

        pIt = this->baseGetReserveIterator();

        pNode = pIt->First();

        // Walk through the nodes
        while(!pIt->IsDone())
        {
            InvBind *pDeleteMe = (InvBind *)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }
    }

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
    void InvBindMan::Create(int reserveNum, int reserveGrow)
    {
        // make sure values are ressonable 
        assert(reserveNum >= 0);
        assert(reserveGrow > 0);

        // initialize the singleton here
        assert(posInstance == nullptr);

        // Do the initialization
        if(posInstance == nullptr)
        {
            posInstance = new InvBindMan(reserveNum, reserveGrow);
        }

    }

    void InvBindMan::Destroy()
    {
        InvBindMan *pMan = InvBindMan::privGetInstance();
        assert(pMan != nullptr);
        AZUL_UNUSED_VAR(pMan);

        delete InvBindMan::posInstance;
        InvBindMan::posInstance = nullptr;
    }

    void InvBindMan::Add(const char *const pFileName, InvBind::Name InvBindName)
    {
        InvBindProto(pFileName, InvBindName);
    }

    void InvBindMan::Add(InvBind::Name InvBindName, unsigned int numMat, Mat4 *poData)
    {
        InvBindMan *pMan = InvBindMan::privGetInstance();

        InvBind *pNode = (InvBind *)pMan->baseAddToFront();
        assert(pNode != nullptr);

        pNode->Set(InvBindName, numMat, poData);
    }

    InvBind *InvBindMan::Find(InvBind::Name _name)
    {
        InvBindMan *pMan = InvBindMan::privGetInstance();
        assert(pMan != nullptr);

        // Compare functions only compares two Nodes

        // So:  Use the Compare Node - as a reference
        //      use in the Compare() function
        pMan->poNodeCompare->mName = _name;

        InvBind *pData = (InvBind *)pMan->baseFind(pMan->poNodeCompare);
        assert(pData);
        return pData;
    }

    void InvBindMan::Remove(InvBind *pNode)
    {
        assert(pNode != nullptr);

        InvBindMan *pMan = InvBindMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseRemove(pNode);
    }

    void InvBindMan::Dump()
    {
        InvBindMan *pMan = InvBindMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseDump();
    }

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
    InvBindMan *InvBindMan::privGetInstance()
    {
        // Safety - this forces users to call Create() first before using class
        assert(posInstance != nullptr);

        return posInstance;
    }

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
    DLink *InvBindMan::derivedCreateNode()
    {
        DLink *pNodeBase = new InvBind();
        assert(pNodeBase != nullptr);

        return pNodeBase;
    }
}

// --- End of File ---
