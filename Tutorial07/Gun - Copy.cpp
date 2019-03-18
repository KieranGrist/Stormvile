#include "Gun.h"



Gun::Gun()
{
}
void Gun::SetUp(XMFLOAT3 Position, XMFLOAT3 Rotation,Transformation Offset)
{
	for (int i = 0; i < 50; i++)
	{
		objbulletlist[i].BulletID = i;
	}
	transform.Position = Position;
	transform.Rotation = Rotation;
	transform.Scale = XMFLOAT3(0, 0, 0);
}
void Gun::Fire()
{
	for (int i = 0; i < 50; i++)
	{
		if (objbulletlist[i].Alive == false)
		{
	
			objbulletlist[i].Start(transform.Position, transform.Rotation);
			objbulletlist[i].Alive = true;
			i = 60;
		}

	}
}
void Gun::Update(Transformation Offset, XMFLOAT3 ForwardDirection,string offsetdirection)
{
	transform.Position = Offset.Position;
	transform.Rotation = Offset.Rotation;

	if (offsetdirection == "Left")
	{
		XMFLOAT3 Left = transform.VectorCrossProduct(XMFLOAT3(0, 1, 0), ForwardDirection);

		transform.Position = transform.VectorSub(transform.Position, Left);

		transform.Position = transform.MultiplyVector(transform.Position, 1.5);
	}
	if (BulletWait <= 0)
	{
		BulletWait = -1;
	}
	if (BulletWait >= 0)
	{


		BulletWait -= 0.0005f;
	}



 	for (int i = 0; i < 50; i++)
	{
		if (objbulletlist[i].Alive == true)
		{
			objbulletlist[i].Update();
			if (objbulletlist[i].TimeOutDestructor >= 200)
			{
				objbulletlist[i].Alive = false;
			}

		}
	}
	
}
Gun::~Gun()
{
}
