//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef INV_BIND_MANAGER_H
#define INV_BIND_MANAGER_H

#include "ManBase.h"
#include "InvBind.h"

namespace Azul
{
    class InvBindMan : public ManBase
    {
        //----------------------------------------------------------------------
        // Static Methods
        //----------------------------------------------------------------------
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        static InvBind *Find(InvBind::Name name);

        static void Remove(InvBind *pNode);
        static void Dump();

        static void Add(const char *const pFileName, InvBind::Name name);
        static void Add(InvBind::Name InvBindName, unsigned int numMat, Mat4 *poInvBindArray);

        //----------------------------------------------------------------------
        // Private methods
        //----------------------------------------------------------------------
    private:
        static InvBindMan *privGetInstance();

        InvBindMan() = delete;
        InvBindMan(const InvBindMan &) = delete;
        InvBindMan &operator=(const InvBindMan &) = delete;
        virtual ~InvBindMan();

        InvBindMan(int reserveNum, int reserveGrow);

        //----------------------------------------------------------------------
        // Override Abstract methods
        //----------------------------------------------------------------------
    protected:
        DLink *derivedCreateNode() override;

        //----------------------------------------------------------------------
        // Data: unique data for this manager 
        //----------------------------------------------------------------------
    private:
        InvBind *poNodeCompare;
        static InvBindMan *posInstance;

    };
}

#endif

//--- End of File ---
