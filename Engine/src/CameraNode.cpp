//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraNode.h"
#include "StringThis.h"

namespace Azul
{

    CameraNode::CameraNode()
        : DLink(),
        poCamera(nullptr)
    {
        this->privClear();
    }

    CameraNode::~CameraNode()
    {
        this->privClear();
    }

    void CameraNode::Set(Camera::Name name, Camera *pCam)
    {
        assert(pCam);
        this->poCamera = pCam;

        this->poCamera->SetName(name);
    }

    Camera *CameraNode::GetCamera()
    {
        return this->poCamera;
    }

    void CameraNode::privClear()
    {
        if(this->poCamera)
        {
            delete this->poCamera;
        }
        this->poCamera = nullptr;
    }

    char *CameraNode::GetName()
    {
        char *pName = nullptr;
        if(this->poCamera)
        {
            pName = this->poCamera->GetName();
        }

        return pName;
    }

    void CameraNode::Wash()
    {
        this->privClear();
    }

    bool CameraNode::Compare(DLink *pTargetNode)
    {
        // This is used in ManBase.Find() 
        assert(pTargetNode);

        CameraNode *pDataB = (CameraNode *)pTargetNode;

        bool status = false;

        assert(pDataB->poCamera);
        assert(this->poCamera);

        if(this->poCamera->name == pDataB->poCamera->name)
        {
            status = true;
        }

        return status;
    }

    void CameraNode::Dump()
    {
        Trace::out("      CameraNode(%p)\n", this);

        // Data:
        if(this->poCamera)
        {
            Trace::out("      Camera(%p) \n", this->poCamera);
            Trace::out("      Name: %s \n", StringMe(this->poCamera->name));
        }
        else
        {
            Trace::out("      Name: %s \n", "null");
        }

        DLink::Dump();
    }
}

// --- End of File ---
