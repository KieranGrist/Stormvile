#include "Bullet.h"



Bullet::Bullet()
{
}
void Bullet::Setup(GameObjectInit Init)
{
	DeltaTime = 0;
	TimeOutDestructor = 0;
	Position = Init.position;
	Rotation = Init.rotation;
	Scale = Init.scale;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
}
void Bullet::Setup(bulletInit Init)
{
	DeltaTime = 0;
	TimeOutDestructor = 0;
	Scale =  Vector3(0.1,0.1, 0.1);
	DrawTexture = Init.DrawTexture;
	Position = Init.GunPos;
	int myRand = rand() % 255;
	Red = (myRand > 128) ? 255 : 0;//@Ternary operator (condition) ? (if true) : (if false)
	Green = (myRand <= 128) ? 255 : 0;
	Blue = 0;
	Pitch = Init.GunRot.x;
	Yaw = Init.GunRot.y;
	ForwardDirection = VectorMaths::EulerAnglesToDirection(Vector3(Pitch, Yaw, 0));
	DrawTexture = Init.DrawTexture;
	//AABB 
	Alive = true;
	Force = MultiplyVector(ForwardDirection, 1000);
	Velocity = Vector3(0, 0, 0);
	Acceleration = Vector3(0, 0, 0);
}
void Bullet::Update()
{
	TimeOutDestructor += DeltaTime;
	MinExtent = VectorSub(Position, Vector3(1, 1, 1));
	MaxExtent = VectorAdd(Position, Vector3(1, 1, 1));
	Mass = 1.0f;
	Acceleration =Force/ Mass;
	Velocity += Acceleration*DeltaTime;
	Position += Velocity*DeltaTime;

//	Force = Vector3(0, 0, 0);
	Draw();
}

Bullet::~Bullet()
{
}
