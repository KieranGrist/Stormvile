#pragma once
#include "DDSTextureLoader.h"
#include "resource.h"
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <string.h>
#include<string>
#include <directxcolors.h>
#include <algorithm> 
#include <SimpleMath.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <random>
#include <stack> 
#include <vector>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <chrono>
#include <atomic>
#include <ctime>
using namespace std;
using namespace DirectX;
using namespace SimpleMath;
class VectorMaths
{public:
	float Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609;
	double clamp(double x, double upper, double lower)
	{
		return min(upper, max(x, lower));
	}

	inline float FloatSquare(Vector3 Square)
	{
		float A;
		float B;
		float C;
		C =
			A = Square.x * Square.x;
		B = Square.y * Square.y;
		C = Square.z * Square.z;
		return A + B + C;
	}
	inline 	Vector2 VectorAdd(Vector2 LHS, Vector2 RHS)
	{
		Vector2 RET;
		RET.x = LHS.x + RHS.x;
		RET.y = LHS.y + RHS.y;
		return RET;
	}
	inline   Vector3 VectorAdd(Vector3 LHS, Vector3 RHS)
	{
		Vector3 RET;
		RET.x = LHS.x + RHS.x;
		RET.y = LHS.y + RHS.y;
		RET.z = LHS.z + RHS.z;
		return RET;
	}
	inline  Vector2 VectorSub(Vector2 LHS, Vector2 RHS)
	{
		Vector2 RET;
		RET.x = LHS.x - RHS.x;
		RET.y = LHS.y - RHS.y;
		return RET;
	}
	inline Vector3 VectorSub(Vector3 LHS, Vector3 RHS)
	{
		Vector3 RET;
		RET.x = LHS.x - RHS.x;
		RET.y = LHS.y - RHS.y;
		RET.z = LHS.z - RHS.z;
		return RET;
	}

	inline  float VectorLength(Vector3 A)
	{
		Vector3 RV;
		float alpha;
		RV = A;
		alpha = RV.x * RV.x + RV.y * RV.y + RV.z * RV.z;
		return sqrt(alpha);
	}
	inline float VectorLengthSq(Vector3 A)
	{
		return A.x * A.x + A.y * A.y + A.z * A.z;
	}
	inline 	Vector3 MultiplyVector(Vector3 LHS, Vector3 RHS)
	{
		Vector3 RET;
		RET.x = LHS.x * RHS.x;
		RET.y = LHS.y * RHS.y;
		RET.z = LHS.z * RHS.x;
		return RET;
	}

	inline Vector3 MultiplyVector(Vector3 A, float scalar)
	{
		Vector3 RV = Vector3(

			A.x * scalar,
			A.y * scalar,
			A.z * scalar);
		return RV;
	}




	inline Vector3 floatSubVector(Vector3 A, float scalar)
	{
		Vector3 RV = Vector3(

			A.x - scalar,
			A.y - scalar,
			A.z - scalar)
			;
		return RV;
	}
	inline Vector3 floatAddVector(Vector3 A, float scalar)
	{
		Vector3 RV = Vector3(

			A.x + scalar,
			A.y + scalar,
			A.z + scalar
		);
		return RV;
	}
	inline Vector3 DivideVector(Vector3 a, float divisor)
	{
		Vector3 RV = Vector3(

			a.x / divisor,
			a.y / divisor,
			a.z / divisor
		);
		return RV;
	}
	inline 	Vector3 VectorNormalized(Vector3 a)
	{
		Vector3 RV = Vector3(a.x, a.y, a.z);
		RV = DivideVector(RV, VectorLength(RV));
		return RV;
	}

	inline 	float DotProduct(Vector3 A, Vector3 B, bool normalise = true)
	{
		float RV;
		Vector3 Vec1 = Vector3(A.x, A.y, A.z);
		Vector3 Vec2 = Vector3(B.x, B.y, A.z);
		if (normalise == true)
		{
			Vec1 = VectorNormalized(Vec1);
			Vec2 = VectorNormalized(Vec2);
		}

		RV = Vec1.x * Vec2.x + Vec1.y * Vec2.y;
		return RV;
	}

	inline 	float VectorToRadians(Vector2 a)
	{
		float RV = 0.0f;
		RV = atan2(a.y, a.x);  // Summary: Returns the arc-tangent of f - the angle in radians whose tangent is f.
		return RV;
	}
	inline 	 Vector2 RadianToVector(float RV)
	{
		//SIN = OPPOSITE
		//COS = ADJACENT
		Vector2 A = Vector2(cos(RV), sin(RV));
		return A;
	}
	inline 	float Deg2Rad(float RV)
	{
		return RV * (Pi / 180);
	}
	inline 	float Rad2Deg(float RV)
	{
		return RV * (180 / Pi);
	}
	inline 	Vector3 EulerAnglesToDirection(Vector2 EulerAngle)
	{
		//takes a 2D vector converts it to a direction then returns
		//Warning this edits X and Z and does not touch Y
		float Pitch = Deg2Rad(EulerAngle.x);
		float Yaw = Deg2Rad(EulerAngle.y);
		Vector3 RV = Vector3
		(
			cos(Yaw) * cos(Pitch),
			0,
			cos(Pitch) *sin(Yaw)
		);
		return RV;
	}
	inline 	Vector3 EulerAnglesToDirection(Vector3 EulerAngle)
	{
		float Pitch = Deg2Rad(EulerAngle.x);
		float Yaw = Deg2Rad(EulerAngle.y);

		Vector3 RV = Vector3
		(
			cos(Yaw) * cos(Pitch),
			sin(Pitch),
			cos(Pitch) *sin(Yaw)
		);
		return RV;
	}
	inline Vector3 EulerAnglesToDirectionRoll(Vector3 EulerAngle)
	{
		Vector3 RV = Vector3();
		RV.x = cos(EulerAngle.z);
		RV.y = sin(EulerAngle.z);
		RV.z = 0;

		return RV;
	}
	inline Vector3 VectorCrossProduct(Vector3 a, Vector3 b, bool normalise = true)
	{
		if (normalise == true)
		{
			a = VectorNormalized(a);
			b = VectorNormalized(b);
		}

		Vector3 C = Vector3();
		C.x = a.y * b.z - a.z * b.y;
		C.y = a.z * b.x - a.x * b.z;
		C.z = a.x * b.y - a.y * b.x;

		return C;
	}
	inline 	Vector3 VecLerp(Vector3 A, Vector3 B, float t)
	{

		Vector3 TempA = MultiplyVector(A, 1.0f - t);
		Vector3 TempB = MultiplyVector(B, t);
		return VectorAdd(TempA, TempB);
	}
};