//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_BASIC_H
#define GAME_OBJECT_BASIC_H

#include "GameObjectRigid.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"

namespace Azul
{
	class GameObjectBasic : public GameObjectRigid
	{
	public:
		GameObjectBasic(GraphicsObject *graphicsObject);

		// Big four
		GameObjectBasic() = delete;
		GameObjectBasic(const GameObjectBasic &) = delete;
		GameObjectBasic &operator=(GameObjectBasic &) = delete;
		virtual ~GameObjectBasic();

		virtual void Update(AnimTime currTime);

		void SetScale(float sx, float sy, float sz);
		void SetQuat(float qx, float qy, float qz, float qw);
		void SetTrans(float x, float y, float z);

		void SetScale(Vec3 &r);
		void SetQuat(Quat &r);
		void SetTrans(Vec3 &r);

	private:
		void privUpdate(AnimTime currTime);

	public:   // add accessors later
		Vec3 *poScale;
		Quat *poQuat;
		Vec3 *poTrans;

		float delta_x;
		float delta_y;
		float delta_z;

		float cur_rot_x;
		float cur_rot_y;
		float cur_rot_z;
	};
}

#endif

// --- End of File ---
