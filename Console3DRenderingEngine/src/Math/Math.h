#ifndef _MATH_H_
#define _MATH_H_



#include "Matrix.h"
#include "Mat2x2.h"
#include "Mat3x3.h"
#include "Mat4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

namespace Math {
	static float fPi = 3.14159265358979323846264338f;
	static double dPi = 3.1415926535897932384626433832795;

	/// <summary>
	/// Converts degrees to radians
	/// </summary>
	/// <param name="degrees"> : angle in degrees </param>
	/// <returns> angle in radians </returns>
	static float fDegToRadian(const float& degrees) { return degrees * fPi / 180.0f; }

	/// <summary>
	/// Converts degrees to radians (doubles version)
	/// </summary>
	/// <param name="degrees"> : angle in degrees (64 bit floating point) </param>
	/// <returns> angle in radians (64 bit floating point) </returns>
	static double dDegToRadian(const double& degrees) { return degrees * dPi / 180.0; }

	/// <summary>
	/// Returns the Mat4x4 that contains Perspective projection matrix for left hand coordinate system
	/// </summary>
	/// <param name="AspectRatio"> : Aspect ratio of the window / screen  (Aspect ratio = height / width) </param>
	/// <param name="FOV"> : Horizontal Field of view of the camera ( or viewport. Whatever you wanna call it )</param>
	/// <param name="ZNear"> : Distance to the near plane from the viewing point </param>
	/// <param name="ZFar"> : Distance to the far plane from the viewing point </param>
	static Mat4x4 Mat4MakeProjectionMatrix(
		const float& AspectRatio,
		const float& FOV,
		const float& ZNear,
		const float& ZFar
	)
	{
		const float fFOVTan = 1.0f / tanf(fDegToRadian(FOV / 2.0f));
		const float fQ = (ZFar) / (ZFar - ZNear);

		return {
			fFOVTan,                  0.0f,         0.0f, 0.0f,
			   0.0f, fFOVTan * AspectRatio,         0.0f, 0.0f,
			   0.0f,                  0.0f,           fQ, 1.0f,
			   0.0f,                  0.0f,  -fQ * ZNear, 0.0f
		};
	}

	/// <summary>
	/// Returns the Mat4x4 that contains Perspective projection matrix for left hand coordinate system
	/// </summary>
	/// <param name="ScreenWidth"> : Width of the screen (or window) in pixels </param>
	/// <param name="ScreenHeight"> : Height of the screen (or window) in pixels </param>
	/// <param name="FOV"> : Horizontal Field of view of the camera ( or viewport. Whatever you wanna call it ) </param>
	/// <param name="ZNear"> : Distance to the near plane from the viewing point </param>
	/// <param name="ZFar"> : Distance to the far plane from the viewing point </param>
	static Mat4x4 Mat4MakeProjectionMatrix(
		const unsigned int& ScreenWidth,
		const unsigned int& ScreenHeight,
		const float& FOV,
		const float& ZNear,
		const float& ZFar
	)
	{
		return Mat4MakeProjectionMatrix(
			(float)ScreenWidth / (float)ScreenHeight,
			FOV,
			ZNear,
			ZFar
		);
	}

	//I think following functions are self documented functions. 


	/// <param name="theta"> : Angle in radians </param>
	static Mat4x4 Mat4MakeRotationZ(const float& theta) {
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		return {
				fCosTheta, fSinTheta, 0.0f, 0.0f,
			   -fSinTheta, fCosTheta, 0.0f, 0.0f,
					 0.0f,      0.0f, 1.0f, 0.0f,
					 0.0f,      0.0f, 0.0f, 1.0f
		};

	}

	/// <param name="theta"> : Angle in radians </param>
	static Mat4x4 Mat4MakeRotationY(const float& theta) {
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		return {
				fCosTheta, 0.0f, -fSinTheta, 0.0f,
					 0.0f, 1.0f,	   0.0f, 0.0f,
				fSinTheta, 0.0f,  fCosTheta, 0.0f,
					 0.0f, 0.0f,       0.0f, 1.0f
		};

	}

	/// <param name="theta"> : Angle in radians </param>
	static Mat4x4 Mat4MakeRotationX(const float& theta) {
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		return {
				1.0f,		0.0f,		0.0f, 0.0f,
				0.0f,  fCosTheta,  fSinTheta, 0.0f,
				0.0f, -fSinTheta,  fCosTheta, 0.0f,
				0.0f,		0.0f,       0.0f, 1.0f
		};

	}

	static Mat4x4 Mat4MakeTranslation(const Vector3& offset) {
		return {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			 offset.x,  offset.y,  offset.z, 1.0f
		};
	}

	static Mat4x4 Mat4MakeTranslation(
		const float& x,
		const float& y,
		const float& z
	)
	{
		return Mat4MakeTranslation({ x,y,z });
	}

	/// <param name="rotation"> : Rotation around x, y, and z axises (in radians) </param>
	static Mat4x4 Mat4MakeRotationZXY(const Vector3& rotation)
	{
		return
			Mat4MakeRotationZ(rotation.z) *
			Mat4MakeRotationX(rotation.x) *
			Mat4MakeRotationY(rotation.y)
			;
	}


	/// <param name="x"> : Rotation around x axis in radians </param>
	/// <param name="y"> : Rotation around y axis in radians </param>
	/// <param name="z"> : Rotation around z axis in radians </param>
	static Mat4x4 Mat4MakeRotationZXY(const float& x, const float& y, const float& z)
	{
		return Mat4MakeRotationZXY({ x, y, z });
	}

	/// <param name="rotation"> : Rotation around x, y, and z axises (in radians) </param>
	static Mat4x4 Mat4MakeRotationXYZ(const Vector3& rotation)
	{
		return
			Mat4MakeRotationX(rotation.x) *
			Mat4MakeRotationY(rotation.y) *
			Mat4MakeRotationZ(rotation.z)
			;
	}

	/// <param name="x"> : Rotation around x axis in radians </param>
	/// <param name="y"> : Rotation around y axis in radians </param>
	/// <param name="z"> : Rotation around z axis in radians </param>
	static Mat4x4 Mat4MakeRotationXYZ(
		const float& x,
		const float& y,
		const float& z
	)
	{
		return Mat4MakeRotationXYZ({ x, y, z });
	}

	/// <param name="rotation"> : Rotation around x, y, and z axises (in radians) </param>
	static Mat4x4 Mat4MakeRotationYXZ(const Vector3& rotation)
	{
		return
			Mat4MakeRotationY(rotation.y) *
			Mat4MakeRotationX(rotation.x) *
			Mat4MakeRotationZ(rotation.z)
			;
	}

	/// <param name="x"> : Rotation around x axis in radians </param>
	/// <param name="y"> : Rotation around y axis in radians </param>
	/// <param name="z"> : Rotation around z axis in radians </param>
	static Mat4x4 Mat4MakeRotationYXZ(
		const float& x,
		const float& y,
		const float& z
	)
	{
		return Mat4MakeRotationYXZ({ x, y, z });
	}


	/// <param name="axis"> : A unit vector that represent the positive direction of the axis </param>
	/// <param name="theta"> : Angle (in radians) around the axis showed by axis parameter </param>
	static Mat4x4 Mat4RotateAroundAxis(const Vector3& axis, const float& theta)
	{
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		const float t = 1 - fCosTheta;

		return{
			t * powf(axis.x,2.0f) + fCosTheta,		t * axis.x * axis.y - fSinTheta * axis.z,	t * axis.x * axis.z + fSinTheta * axis.y,	0.0f,
			t * axis.x * axis.y + fSinTheta * axis.z,	t * powf(axis.y,2) + fCosTheta,		t * axis.y * axis.z - fSinTheta * axis.x,	0.0f,
			t * axis.x * axis.z - fSinTheta * axis.y,	t * axis.y * axis.z + fSinTheta * axis.x,	t * powf(axis.z,2) + fCosTheta,		0.0f,
			0.0f,										0.0f,										0.0f,										1.0f

		};
	}

	/// <param name="theta"> : Angle in radians </param>
	static Mat3x3 Mat3MakeRotationZ(const float& theta)
	{
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		return {
				fCosTheta, fSinTheta, 0.0f,
			   -fSinTheta, fCosTheta, 0.0f,
					 0.0f,      0.0f, 1.0f

		};

	}
	/// <param name="theta"> : Angle in radians </param>
	static Mat3x3 Mat3MakeRotationY(const float& theta)
	{
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		return {
				fCosTheta, 0.0f, -fSinTheta,
					 0.0f, 1.0f,	   0.0f,
				fSinTheta, 0.0f,  fCosTheta
		};

	}

	/// <param name="theta"> : Angle in radians </param>
	static Mat3x3 Mat3MakeRotationX(const float& theta)
	{
		const float fSinTheta = sinf(theta);
		const float fCosTheta = cosf(theta);

		return {
				1.0f,		0.0f,		0.0f,
				0.0f,  fCosTheta,  fSinTheta,
				0.0f, -fSinTheta,  fCosTheta
		};

	}

	/// <param name="rotation"> : Rotation around x, y, and z axises (in radians) </param>
	static Mat3x3 Mat3MakeRotationZXY(const Vector3& rotation)
	{
		return Mat3MakeRotationZ(rotation.z) * Mat3MakeRotationX(rotation.x) * Mat3MakeRotationY(rotation.y);
	}

	/// <param name="x"> : Rotation around x axis in radians </param>
	/// <param name="y"> : Rotation around y axis in radians </param>
	/// <param name="z"> : Rotation around z axis in radians </param>
	static Mat3x3 Mat3MakeRotationZXY(
		const float& x,
		const float& y,
		const float& z
	)
	{
		return Mat3MakeRotationZXY({ x, y, z });
	}

	/// <param name="rotation"> : Rotation around x, y, and z axises (in radians) </param>
	static Mat3x3 Mat3MakeRotationXYZ(const Vector3& rotation)
	{
		return
			Mat3MakeRotationX(rotation.x) *
			Mat3MakeRotationY(rotation.y) *
			Mat3MakeRotationZ(rotation.z)
			;
	}

	/// <param name="x"> : Rotation around x axis in radians </param>
	/// <param name="y"> : Rotation around y axis in radians </param>
	/// <param name="z"> : Rotation around z axis in radians </param>
	static Mat3x3 Mat3MakeRotationXYZ(
		const float& x,
		const float& y,
		const float& z
	)
	{
		return Mat3MakeRotationXYZ({ x, y, z });
	}

	/// <param name="rotation"> : Rotation around x, y, and z axises (in radians) </param>
	static Mat3x3 Mat3MakeRotationYXZ(const Vector3& rotation)
	{
		return
			Mat3MakeRotationY(rotation.y) *
			Mat3MakeRotationX(rotation.x) *
			Mat3MakeRotationZ(rotation.z)
			;
	}

	/// <param name="x"> : Rotation around x axis in radians </param>
	/// <param name="y"> : Rotation around y axis in radians </param>
	/// <param name="z"> : Rotation around z axis in radians </param>
	static Mat3x3 Mat3MakeRotationYXZ(
		const float& x,
		const float& y,
		const float& z
	)
	{
		return Mat3MakeRotationYXZ({ x, y, z });
	}

	/// <param name="axis"> : A unit vector that represent the positive direction of the axis </param>
	/// <param name="theta"> : Angle (in radians) around the axis showed by axis parameter </param>
	static Mat3x3 Mat3MakeRotationAroundAxis(
		const float& theta,
		const Vector3& axis
	)
	{
		const float& fCosTheta = cosf(theta); const float& fSinTheta = sinf(theta);


		return{
			fCosTheta + powf(axis.x, 2.0f) * (1.0f - fCosTheta)	,		axis.x * axis.y * (1.0f - fCosTheta) - axis.z * fSinTheta	,		axis.x * axis.z * (1.0f - fCosTheta) + axis.y * fSinTheta,
			axis.y * axis.x * (1.0f - fCosTheta) + axis.z * fSinTheta	,		fCosTheta + powf(axis.y, 2.0f) * (1.0f - fCosTheta)	,		axis.y * axis.z * (1.0f - fCosTheta) - axis.x * fSinTheta,
			axis.z * axis.x * (1.0f - fCosTheta) - axis.y * fSinTheta	,		axis.z * axis.y * (1.0f - fCosTheta) + axis.x * fSinTheta	,		fCosTheta + powf(axis.z, 2.0f) * (1.0f - fCosTheta)
		};
	}

	static Vector3 Vec3CrossProduct(
		const Vector3& a,
		const Vector3& b
	)
	{
		return Vector3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	static Vector4 Vec4CrossProduct(
		const Vector4& a,
		const Vector4& b
	)
	{
		return Vector4(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	static float Vec2DotProduct(
		const Vector2& a,
		const Vector2& b
	)
	{
		return
			a.x * b.x + a.y * b.y;
		;
	}

	static float Vec3DotProduct(
		const Vector3& a,
		const Vector3& b
	)
	{
		return
			a.x * b.x + a.y * b.y + a.z * b.z
			;
	}

	static float Vec4DotProduct(
		const Vector4& a,
		const Vector4& b
	)
	{
		return
			a.x * b.x + a.y * b.y + a.z * b.z
			;
	}

	template<typename T>
	//A function for Inerpolating between src and dst based on alpha. This is a templated function so any object that support adding, substracting and multiplying with a constant operations will be able to interpolate. 
	static inline T Interpolate(
		const T& src,
		const T& dst,
		const float& alpha
	)
	{
		return src + (dst - src) * alpha;
	}
}

#endif // !_MATH_H_
