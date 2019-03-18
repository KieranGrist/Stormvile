#include "Bullet.h"



Bullet::Bullet()
{
}
void Bullet::Start(XMFLOAT3 GunPos,XMFLOAT3 GunRot)
{

	TimeOutDestructor = 0;
	transform.Scale =  XMFLOAT3(0.1, 0.1, 0.1);

	transform.Position = GunPos;
	Pitch = GunRot.x;
	Yaw = GunRot.y;
	ForwardDirection = transform.EulerAnglesToDirection(XMFLOAT3(Pitch, Yaw, 0));

	//AABB 
	transform.Update();
	Alive = true;
}
void Bullet::Update()
{
	transform.Update();
	//Check Grid Bullet is in
	//GridID =CollDet Against GridList.ID

	TimeOutDestructor += 0.0005;
	ForwardDirection = transform.EulerAnglesToDirection(XMFLOAT3(Pitch, Yaw, 0));
	XMFLOAT3 FowardTimesed = transform.MultiplyVector(ForwardDirection, 0.0002);
	//Velocity = transform.Vectoradd(FowardTimesed, Velocity);

	transform.Position = transform.Vectoradd(transform.Position, FowardTimesed);

	transform.Draw();
}

Bullet::~Bullet()
{
}
