#include "Bullet.h"



Bullet::Bullet()
{
}
void Bullet::Setup(GameObjectInit Init)
{
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

	TimeOutDestructor = 0;
	Scale =  Vector3(0.1,0.1, 0.1);
	DrawTexture = Init.DrawTexture;
	Position = Init.GunPos;
	Velocity = Init.Velocity;
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
	Force = MultiplyVector(ForwardDirection, 10000);
	Velocity = Vector3(0, 0, 0);
	Acceleration = Vector3(0, 0, 0);
}
void Bullet::Update()
{
	MinExtent = VectorSub(Position, Vector3(1, 1, 1));
	MaxExtent = VectorAdd(Position, Vector3(1, 1, 1));
	Mass = 1.1f;
	Acceleration = DivideVector(Force, Mass);
	Velocity = VectorAdd(Velocity, MultiplyVector(Acceleration, 0.01f));
	Position = VectorAdd(Position, MultiplyVector(Velocity, 0.01f));
	TimeOutDestructor += 0.05;
	Force = Vector3(0, 0, 0);
	Draw();
}

Bullet::~Bullet()
{
}
