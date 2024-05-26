//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Mesh.h"

namespace Azul
{
	class CameraMesh : public Mesh
	{
	public:
		static const unsigned int TRIANGLE_COUNT = 8;
		static const unsigned int VERT_COUNT = 9;

	public:
		CameraMesh();
		CameraMesh(const CameraMesh &) = delete;
		CameraMesh &operator=(const CameraMesh &other) = delete;
		virtual ~CameraMesh();

		void update();

	private:
		void privUpdate();
	};

}
#endif

// --- End of File ---
