//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HierarchyMan.h"
#include "DLinkMan.h"
#include "HierarchyProto.h"

namespace Azul
{

    HierarchyMan *HierarchyMan::posInstance = nullptr;

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    HierarchyMan::HierarchyMan(int reserveNum, int reserveGrow)
        : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
    {
        // Preload the reserve
        this->proFillReservedPool(reserveNum);

        // initialize derived data here
        this->poNodeCompare = new Hierarchy();
    }

    HierarchyMan::~HierarchyMan()
    {
        delete this->poNodeCompare;
        this->poNodeCompare = nullptr;

        // iterate through the list and delete
        Iterator *pIt = this->baseGetActiveIterator();

        DLink *pNode = pIt->First();

        // Walk through the nodes
        while(!pIt->IsDone())
        {
            Hierarchy *pDeleteMe = (Hierarchy *)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }

        pIt = this->baseGetReserveIterator();

        pNode = pIt->First();

        // Walk through the nodes
        while(!pIt->IsDone())
        {
            Hierarchy *pDeleteMe = (Hierarchy *)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }
    }

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
    void HierarchyMan::Create(int reserveNum, int reserveGrow)
    {
        // make sure values are ressonable 
        assert(reserveNum >= 0);
        assert(reserveGrow > 0);

        // initialize the singleton here
        assert(posInstance == nullptr);

        // Do the initialization
        if(posInstance == nullptr)
        {
            posInstance = new HierarchyMan(reserveNum, reserveGrow);
        }

    }

    void HierarchyMan::Destroy()
    {
        HierarchyMan *pMan = HierarchyMan::privGetInstance();
        assert(pMan != nullptr);
        AZUL_UNUSED_VAR(pMan);

        delete HierarchyMan::posInstance;
        HierarchyMan::posInstance = nullptr;
    }

    void HierarchyMan::Add(const char *const pFileName, Hierarchy::Name hierarchyName)
    {
        HierarchyProto(pFileName, hierarchyName);
    }

    void HierarchyMan::Add(Hierarchy::Name hierarchyName, unsigned int numBones, unsigned int depth, int *poData)
    {
        HierarchyMan *pMan = HierarchyMan::privGetInstance();

        Hierarchy *pNode = (Hierarchy *)pMan->baseAddToFront();
        assert(pNode != nullptr);

        pNode->Set(hierarchyName, numBones, depth, poData);
    }

    Hierarchy *HierarchyMan::Find(Hierarchy::Name _name)
    {
        HierarchyMan *pMan = HierarchyMan::privGetInstance();
        assert(pMan != nullptr);

        // Compare functions only compares two Nodes

        // So:  Use the Compare Node - as a reference
        //      use in the Compare() function
        pMan->poNodeCompare->mName = _name;

        Hierarchy *pData = (Hierarchy *)pMan->baseFind(pMan->poNodeCompare);
        assert(pData);
        return pData;
    }

    void HierarchyMan::Remove(Hierarchy *pNode)
    {
        assert(pNode != nullptr);

        HierarchyMan *pMan = HierarchyMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseRemove(pNode);
    }

    void HierarchyMan::Dump()
    {
        HierarchyMan *pMan = HierarchyMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseDump();
    }

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
    HierarchyMan *HierarchyMan::privGetInstance()
    {
        // Safety - this forces users to call Create() first before using class
        assert(posInstance != nullptr);

        return posInstance;
    }

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
    DLink *HierarchyMan::derivedCreateNode()
    {
        DLink *pNodeBase = new Hierarchy();
        assert(pNodeBase != nullptr);

        return pNodeBase;
    }
}

// --- End of File ---
