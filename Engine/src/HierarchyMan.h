//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef HIERARCHY_MANAGER_H
#define HIERARCHY_MANAGER_H

#include "ManBase.h"
#include "Hierarchy.h"

namespace Azul
{
    class HierarchyMan : public ManBase
    {
        //----------------------------------------------------------------------
        // Static Methods
        //----------------------------------------------------------------------
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        static Hierarchy *Find(Hierarchy::Name name);

        static void Remove(Hierarchy *pNode);
        static void Dump();

        static void Add(const char *const pFileName, Hierarchy::Name name);
        static void Add(Hierarchy::Name hierarchyName, unsigned int numBones, unsigned int depth, int *poHierarchyTable);

        //----------------------------------------------------------------------
        // Private methods
        //----------------------------------------------------------------------
    private:
        static HierarchyMan *privGetInstance();

        HierarchyMan() = delete;
        HierarchyMan(const HierarchyMan &) = delete;
        HierarchyMan &operator=(const HierarchyMan &) = delete;
        virtual ~HierarchyMan();

        HierarchyMan(int reserveNum, int reserveGrow);

        //----------------------------------------------------------------------
        // Override Abstract methods
        //----------------------------------------------------------------------
    protected:
        DLink *derivedCreateNode() override;

        //----------------------------------------------------------------------
        // Data: unique data for this manager 
        //----------------------------------------------------------------------
    private:
        Hierarchy *poNodeCompare;
        static HierarchyMan *posInstance;

    };
}

#endif

//--- End of File ---
