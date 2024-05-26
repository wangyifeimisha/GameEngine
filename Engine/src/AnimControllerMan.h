#pragma once
//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIMCONTROLLER_MANAGER_H
#define ANIMCONTROLLER_MANAGER_H

#include "ManBase.h"
#include "AnimController.h"


namespace Azul
{
    class AnimControllerMan : public ManBase
    {
        //----------------------------------------------------------------------
        // Static Methods
        //----------------------------------------------------------------------
    public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();

        //static AnimController* Find(AnimController::Name name);

        static void Remove(AnimController* pNode);
        static void Dump();

        static void Add(AnimController* pAnimController);
        //static void Add(AnimController::Name AnimControllerName, unsigned int numBones, AnimControllerEntry* poAnimControllerEntry);
        
        void Update();

        //----------------------------------------------------------------------
        // Private methods
        //----------------------------------------------------------------------
    private:
        static AnimControllerMan* privGetInstance();

        AnimControllerMan() = delete;
        AnimControllerMan(const AnimControllerMan&) = delete;
        AnimControllerMan& operator=(const AnimControllerMan&) = delete;
        virtual ~AnimControllerMan();

        AnimControllerMan(int reserveNum, int reserveGrow);

        //----------------------------------------------------------------------
        // Override Abstract methods
        //----------------------------------------------------------------------
    protected:
        DLink* derivedCreateNode() override;

        //----------------------------------------------------------------------
        // Data: unique data for this manager 
        //----------------------------------------------------------------------
    private:
        AnimController* poNodeCompare;
        static AnimControllerMan* posInstance;

        

    };

}

#endif