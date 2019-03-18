#include "Player.h"



Player::Player()
{
}

void Player::Setup(playerInit Init)
{

	ForwardDirection = Vector3(0, 0, 0);
	GameObjectInit Temp;
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	DrawTexture = Init.DrawTexture;
	Temp.DrawTexture = Init.DrawTexture;
	Setup(Temp);
	Health = Init.Health;
	Shots = Init.Shots;


}
void Player::Setup(GameObjectInit Init)
{
	Position = Init.position;
	Scale = Init.scale;
	Rotation = Init.rotation;
	Blue = Init.ColourB;
	Green = Init.ColourG;
	Red = Init.ColourR;
	DrawTexture = Init.DrawTexture;
}
void Player::Update()
{
	MinExtent = VectorSub(Position, Vector3(1, 1, 1));
	MaxExtent = VectorAdd(Position, Vector3(1, 1, 1));
	//LEFT handed system 
	ForwardDirection = EulerAnglesToDirection(Vector3(PITCH, YAW, 0));
	RightDirecton = VectorCrossProduct(Vector3(0, 1, 0), ForwardDirection);
	UpDirection = VectorCrossProduct(ForwardDirection, RightDirecton);
	Mass = 1;



	if (A == true)
	{
		YAW += Sensertivity;
	}
	if (D == true)
	{
		YAW -= Sensertivity;
	}
	if (W == true)
	{
		PITCH -= Sensertivity;
	}
	if (S == true)
	{
		PITCH += Sensertivity;
	}
	PITCH = clamp(PITCH, 89, -89);
	Sensertivity = clamp(Sensertivity, 0.5, -0.5);
	/*
	LEFT, RIGHT = THRUSTERS LEFT AND RIGHT
	UP, DOWN = THRUSTERS FOWARD AND BACKWARDS
	SPACE, CONTROL = THRUSTERS UP AND DOWN;
	X = DAMPNERS
	WASD = SHIP ROTATION



	*/
	if (LEFT == true)
	{
		Force = VectorSub(Force, MultiplyVector(RightDirecton, 10));
	}
	if (RIGHT == true)
	{
		Force = VectorAdd(Force, MultiplyVector(RightDirecton, 10));
	}
	if (X == true)
	{
		Velocity = DivideVector(Velocity, 1.01f);
		//		Velocity = DivideVector(Velocity, );
	}
	if (UP == true)
	{
		Force = VectorAdd(Force, MultiplyVector(ForwardDirection, 10));
	}
	if (DOWN == true)
	{
		Force = VectorSub(Force, MultiplyVector(ForwardDirection, 10));
	}
	if (SPACE == true)
	{
		Force = VectorAdd(Force, MultiplyVector(Vector3(UpDirection), 10));
	}
	if (CONTROL == true)
	{
		Force = VectorSub(Force, MultiplyVector(Vector3(UpDirection), 10));
	}
	if (PLUS == true)
	{
		Sensertivity += 0.0005f;
	}
	if (MINUS == true)
	{
		Sensertivity -= 0.0005f;
	}

	initGun GunTemp;
	GunTemp.Position = Position;
	GunTemp.Rotation = Rotation;
	GunTemp.Velocity = Velocity;
	GunTemp.ForwardDirection = ForwardDirection;
	GunTemp.offsetdirection = "Left";
	GunTemp.DrawTexture = DrawTexture;
	objGunLeft.Setup(GunTemp);
	GunTemp.Position = Position;
	GunTemp.Rotation = Rotation;
	GunTemp.Velocity = Velocity;
	GunTemp.ForwardDirection = ForwardDirection;
	GunTemp.offsetdirection = "Right";
	GunTemp.DrawTexture = DrawTexture;
	objGunRight.Setup(GunTemp);
	if (F == true)
	{
		if (objGunLeft.BulletWait <= 0)
		{

			objGunLeft.BulletWait = 1;

			objGunLeft.Fire();
			Shots += 1;
		}
		if (objGunRight.BulletWait <= 0)
		{
			objGunRight.BulletWait = 1;
			objGunRight.Fire();
			Shots += 1;
			F = false;


		}

}
	objGunLeft.Update();
	objGunRight.Update();
	Acceleration = DivideVector(Force , Mass);
	Velocity =VectorAdd(Velocity, MultiplyVector(Acceleration ,0.01f));
	Position = VectorAdd(Position, MultiplyVector(Velocity,0.01f));
	Rotation = Vector3(PITCH,YAW,0);
	Force = Vector3(0, 0, 0);	
}

Player::~Player()
{
}