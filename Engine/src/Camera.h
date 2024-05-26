//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"

namespace Azul
{
	class Camera : public Align16
	{
	public:

		enum class Type
		{
			PERSPECTIVE_3D,
			ORTHOGRAPHIC_2D
		};


		enum class Name
		{
			CAMERA_0,
			CAMERA_1,
			NOT_INITIALIZED,
			NullCamera
		};

	public:
		// Default constructor
		Camera() = delete;
		Camera(const Camera &) = delete;
		Camera &operator = (const Camera &) = delete;
		virtual ~Camera();

		Camera(Camera::Type _camType);

		// Setup on single camera
		void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);

		// w1(7) 
		void setOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);

		void setViewport(const int inX, const int inY, const int width, const int height);
		void setOrientAndPosition(const Vec3 &Up_vect, const Vec3 &inLookAt_pt, const Vec3 &pos_pt);

		// update camera system
		void updateCamera(void);

		// Get the matrices for rendering
		Mat4 &getViewMatrix();
		Mat4 &getProjMatrix();

		// accessors
		void getPos(Vec3 &outPos) const;
		void getDir(Vec3 &outDir) const;
		void getUp(Vec3 &outUp) const;
		void getLookAt(Vec3 &outLookAt) const;
		void getRight(Vec3 &outRight) const;

		int getScreenWidth() const;
		int getScreenHeight() const;

		// Why no SETS?  Pos,Dir,Up,LookAt, Right
		//   They have to be adjust together in setOrientAndPosition()

		void getFieldOfView(float &Value) const;
		void setFieldOfView(const float Value);

		void getNearDist(float &Value) const;
		void setNearDist(const float Value);

		// accessors
			// w1(7)
		Camera::Type getType() const;

		char *GetName() const;
		void SetName(Camera::Name name);

		// helper functions
		void GetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos, Vec3 &upNorm, Vec3 &forwardNorm, Vec3 &rightNorm);
		void SetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos);

		void getNearTopLeft(Vec3 &vOut) const;
		void getNearTopRight(Vec3 &vOut) const;
		void getNearBottomLeft(Vec3 &vOut) const;
		void getNearBottomRight(Vec3 &vOut) const;
		void getFarTopLeft(Vec3 &vOut) const;
		void getFarTopRight(Vec3 &vOut) const;
		void getFarBottomLeft(Vec3 &vOut) const;
		void getFarBottomRight(Vec3 &vOut) const;

	private:  // methods should never be public
		void privSetViewState(void);
		void privCalcPlaneHeightWidth(void);
		void privCalcFrustumVerts(void);
		void privCalcFrustumCollisionNormals(void);
		void privUpdateProjectionMatrix(void);
		void privUpdateViewMatrix(void);


	private:  // data  (Keep it private)

		// -------------------------------------------------------
		// 16-bit aligned data below this point:
		// -------------------------------------------------------

		// Projection Matrix
		Mat4	projMatrix;
		Mat4	viewMatrix;

		// camera unit vectors (up, dir, right)
		Vec3	vDir;
		Vec3	vRight;  // derived by up and dir


		Vec3	vUp;      // Up vector
		Vec3	vPos;     // pos pt
		Vec3	vLookAt;  // target pt

		// world space coords for viewing frustum
		Vec3	nearTopLeft;
		Vec3	nearTopRight;
		Vec3	nearBottomLeft;

		Vec3	nearBottomRight;
		Vec3	farTopLeft;
		Vec3	farTopRight;
		Vec3	farBottomLeft;

		Vec3	farBottomRight;

		// Normals of the frustum
		Vec3	frontNorm;
		Vec3	backNorm;
		Vec3	rightNorm;

		Vec3	leftNorm;
		Vec3	topNorm;
		Vec3	bottomNorm;

		// -------------------------------------------------------
		// unaligned data below this point:
		// -------------------------------------------------------

		// w1(7)
		Camera::Type camType;

		// Define the frustum inputs
		float	nearDist;
		float	farDist;
		float	fovy;
		float	aspectRatio;

		// Screen size in world space
		float	near_height;
		float	near_width;
		float	far_height;
		float	far_width;

		// w1(7)
		// Ortho hacks 
		float	xMin;
		float	yMin;
		float	zMin;
		float	xMax;
		float	yMax;
		float	zMax;

		// viewports
		int		viewport_x;
		int		viewport_y;
		int		viewport_width;
		int		viewport_height;

		// Name
	public:
		Camera::Name name;
		char pad[12];
	};
}

#endif

// --- End of File ---