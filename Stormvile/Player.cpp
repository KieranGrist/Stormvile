#include "Player.h"



Player::Player()
{
	MinPoints = XMFLOAT3(10000, 10000, 1000);
	MaxPoints = XMFLOAT3(-10000, -10000, -1000);
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
	Velocity = Vector3(0, 0, 0);
	PITCH = 0;
	YAW = 0;
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
   //Health = 100;

	MinExtent = VectorSub(Position, Vector3(MinPoints));
	MaxExtent = VectorAdd(Position, Vector3(MaxPoints));
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
	PITCH = clamp(PITCH, 89.99, -89.99);
	Sensertivity = clamp(Sensertivity, 2, -0.5);
	/*
	LEFT, RIGHT = THRUSTERS LEFT AND RIGHT
	UP, DOWN = THRUSTERS FOWARD AND BACKWARDS
	SPACE, CONTROL = THRUSTERS UP AND DOWN;
	X = DAMPNERS
	WASD = SHIP ROTATION



	*/
	if (LEFT == true)
	{
		Force -= RightDirecton * 100;
	}
	if (RIGHT == true)
	{
		Force += RightDirecton * 100;
	}
	if (X == true)
	{
		Velocity /= 1.01f;
		//		Velocity = DivideVector(Velocity, );
	}
	if (UP == true)
	{
		Force += ForwardDirection * 100;
	}
	if (DOWN == true)
	{
		Force -= ForwardDirection * 100;
	}
	if (SPACE == true)
	{
		Force += UpDirection * 100;
	}
	if (CONTROL == true)
	{
		Force -= UpDirection * 100;
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
	objGunLeft.DeltaTime = DeltaTime;
	objGunLeft.Setup(GunTemp);
	GunTemp.Position = Position;
	GunTemp.Rotation = Rotation;
	GunTemp.Velocity = Velocity;
	GunTemp.ForwardDirection = ForwardDirection;
	GunTemp.offsetdirection = "Right";
	GunTemp.DrawTexture = DrawTexture;
	objGunRight.DeltaTime = DeltaTime;
	objGunRight.Setup(GunTemp);
	objGunLeft.Update();
	objGunRight.Update();
	if (F == true)
	{	
		if (objGunLeft.BulletWait >= 0.25)
		{
			objGunLeft.BulletWait = 0;

			if (objGunLeft.Fire() == true)
			{
				Shots += 1;
			}
	
		}
		if (objGunRight.BulletWait >= 0.25)
		{
	
			objGunRight.BulletWait = 0;
			if (objGunRight.Fire() == true)
			{
				Shots += 1;
			}
			F = false;


		}

}
	objGunLeft.Update();
	objGunRight.Update();

Velocity /= 1.01f;
	Acceleration = Force / Mass;
	Velocity += Acceleration *DeltaTime;
	Position += Velocity* DeltaTime;
	Rotation = Vector3(PITCH,YAW,0);
	Force = Vector3(0, 0, 0);	
}

Player::~Player()
{
}
