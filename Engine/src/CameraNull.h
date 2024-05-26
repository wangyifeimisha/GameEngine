//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_NULL_H
#define CAMERA_NULL_H

#include "Camera.h"

namespace Azul
{
	class CameraNull : public Camera
	{
	public:
		CameraNull();
		CameraNull(const CameraNull &) = delete;
		CameraNull &operator=(const CameraNull &other) = delete;
		virtual ~CameraNull();


	private:

	};
}

#endif

// --- End of File ---
