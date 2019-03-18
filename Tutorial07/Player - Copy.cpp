#include "Player.h"



Player::Player()
{
}
void Player::Setup(XMFLOAT3 Position, XMFLOAT3 Rotation, XMFLOAT3 Scale, float health, float shots)
{
	ForwardDirection = XMFLOAT3(0, 0, 0);
	transform.Setup(Position, Rotation, Scale, 0, 0, 0);
	Health = health;
	Shots = shots;

	objGun.SetUp(Position, Rotation,transform);
}
void Player::Update()
{
	//LEFT handed system 
	ForwardDirection = transform.EulerAnglesToDirection(XMFLOAT3(PITCH, YAW, 0));
	RightDirecton = transform.VectorCrossProduct(XMFLOAT3(0, 1, 0), ForwardDirection);

	if (A == true)
	{
		YAW += 0.005f;
	}
	if (D == true)
	{
		YAW -= 0.005f;
	}

}
//
//void Player::Update()
//{
//	//LEFT handed system 
//	ForwardDirection = transform.EulerAnglesToDirection(XMFLOAT3(PITCH, YAW, 0));
//	RightDirecton = transform.VectorCrossProduct(XMFLOAT3(0, 1, 0), ForwardDirection);
//	if (W == true)
//	{
//		PITCH -= 0.005F;
//	}
//	if (S == true)
//	{
//		PITCH += 0.005F;
//	}
//	if (SHIFT == true)
//	{
//		Velocity = transform.Vectoradd(Velocity, ForwardDirection);
//		Velocity = transform.MultiplyVector(Velocity, 0.001);
//		SHIFT = false;
//	}
//	if (CONTROL == true)
//	{
//		Velocity = transform.VectorSub(Velocity, ForwardDirection);
//		Velocity = transform.MultiplyVector(Velocity, 0.001);
//		CONTROL = false;
//	}
//	if (A == true)
//	{
//		Velocity = transform.VectorSub(Velocity, RightDirecton);
//		Velocity = transform.MultiplyVector(Velocity, 0.00025);
//		A = false;
//	}
//	if (D == true)
//	{
//		Velocity = transform.Vectoradd(Velocity, RightDirecton);
//		Velocity = transform.MultiplyVector(Velocity, 0.00025);
//		D = false;
//	}
//
//	if (Q == true)
//	{
//		YAW -= 0.02f;
//		Q = false;
//	}
//	if (E == true)
//	{
//		YAW += 0.02f;
//		E = false;
//	}
//	if (X == true)
//	{
//		Velocity = transform.MultiplyVector(Velocity, 0.9);
//		X = false;
//	}
//
//	if (objGun.BulletWait <= 0)
//	{
//	if (SPACE == true)
//	{
//		objGun.BulletWait = 1;
//		objGun.Fire();
//		SPACE = false;
//	}
//	}
//	//Velocity = transform.MultiplyVector(Velocity, 0.1);
//	int MaxExtent = 50;
//	if (PITCH >= MaxExtent)
//	{
//		PITCH = MaxExtent;
//	}
//	if (PITCH <= -MaxExtent)
//	{
//		PITCH = -MaxExtent;
//	}
//	objGun.Update(transform, ForwardDirection, "Left");
//	transform.Position = transform.Vectoradd(transform.Position, Velocity);
//
//	transform.Rotation = XMFLOAT3(PITCH,YAW ,0);
//
//	transform.Update();
//
////	transform.Draw();
//}

Player::~Player()
{
}
