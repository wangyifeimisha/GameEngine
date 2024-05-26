//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraDemoInput.h"
#include "CameraMan.h"

namespace Azul
{
	void CameraDemoInput()
	{

		if((GetKeyState('0') & 0x8000))
		{
			CameraMan::SetCurrent(Camera::Name::CAMERA_0, Camera::Type::PERSPECTIVE_3D);
		}

		if((GetKeyState('1') & 0x8000))
		{
			CameraMan::SetCurrent(Camera::Name::CAMERA_1, Camera::Type::PERSPECTIVE_3D);
		}

		if((GetKeyState('I') & 0x8000))
		{
			Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);

			Vec3 pos;
			Vec3 tar;
			Vec3 up;
			Vec3 upNorm;
			Vec3 forwardNorm;
			Vec3 rightNorm;

			pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			//	tar = obj;

			pos = pos + 0.03f * forwardNorm;
			//tar = tar + 0.03f * forwardNorm;
			up = up + 0.03f * forwardNorm;

			pCam->SetHelper(up, tar, pos);
		}

		if((GetKeyState('O') & 0x8000))
		{
			Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);

			Vec3 pos;
			Vec3 tar;
			Vec3 up;
			Vec3 upNorm;
			Vec3 forwardNorm;
			Vec3 rightNorm;

			pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			//tar = obj;

			pos = pos - 0.03f * forwardNorm;
			up = up - 0.03f * forwardNorm;

			pCam->SetHelper(up, tar, pos);

		}


		if((GetKeyState(VK_RIGHT) & 0x8000))
		{
			Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);

			Vec3 pos;
			Vec3 tar;
			Vec3 up;
			Vec3 upNorm;
			Vec3 forwardNorm;
			Vec3 rightNorm;

			pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			//	tar = obj;

			Trans T1(tar);
			Trans nT1(-tar);

			Rot R1;
			R1.set(Axis::AxisAngle, upNorm, +0.03f);

			Mat4 M = nT1 * R1 * T1;

			up = Vec4(up, 1) * M;
			pos = Vec4(pos, 1) * M;
			tar = Vec4(tar, 1) * M;

			pCam->SetHelper(up, tar, pos);
		}



		if((GetKeyState(VK_LEFT) & 0x8000))
		{
			Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);

			Vec3 pos;
			Vec3 tar;
			Vec3 up;
			Vec3 upNorm;
			Vec3 forwardNorm;
			Vec3 rightNorm;

			pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm

		//	tar = obj;

			Trans T1(tar);
			Trans nT1(-tar);

			Rot R1;
			R1.set(Axis::AxisAngle, upNorm, -0.03f);

			Mat4 M = nT1 * R1 * T1;

			up = Vec4(up, 1) * M;
			pos = Vec4(pos, 1) * M;
			tar = Vec4(tar, 1) * M;

			pCam->SetHelper(up, tar, pos);
		}

		if((GetKeyState(VK_DOWN) & 0x8000))
		{
			Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);

			Vec3 pos;
			Vec3 tar;
			Vec3 up;
			Vec3 upNorm;
			Vec3 forwardNorm;
			Vec3 rightNorm;

			pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			//	tar = obj;


				// OK, now 3 points... pos, tar, up
				//     now 3 normals... upNorm, forwardNorm, rightNorm

			Trans T1(tar);
			Trans nT1(-tar);
			Rot R1;
			R1.set(Axis::AxisAngle, rightNorm, 0.03f);

			Mat4 M = nT1 * R1 * T1;

			up = Vec4(up, 1) * M;
			pos = Vec4(pos, 1) * M;
			tar = Vec4(tar, 1) * M;

			pCam->SetHelper(up, tar, pos);
		}

		if((GetKeyState(VK_UP) & 0x8000))
		{
			Camera *pCam = CameraMan::Find(Camera::Name::CAMERA_0);

			Vec3 pos;
			Vec3 tar;
			Vec3 up;
			Vec3 upNorm;
			Vec3 forwardNorm;
			Vec3 rightNorm;

			pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			//tar = obj;

			Trans T1(tar);
			Trans nT1(-tar);
			Rot R1;
			R1.set(Axis::AxisAngle, rightNorm, -0.03f);

			Mat4 M = nT1 * R1 * T1;

			up = Vec4(up, 1) * M;
			pos = Vec4(pos, 1) * M;
			tar = Vec4(tar, 1) * M;

			pCam->SetHelper(up, tar, pos);
		}

	}

}

// --- End of File ---
