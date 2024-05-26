//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraNull.h"
#include "Camera.h"

namespace Azul
{

	CameraNull::CameraNull()
		: Camera(Camera::Type::PERSPECTIVE_3D)
	{

	}

	CameraNull::~CameraNull()
	{
		// remove anything dynamic here
	}

}

// --- End of File ---
