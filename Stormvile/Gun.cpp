#include "Gun.h"



Gun::Gun()
{
	objbulletlist = new Bullet[50];
	//Memory Pooling
}
void Gun::Setup(initGun Init)
{
	for (int i = 0; i < 50; i++)
	{
		objbulletlist[i].BulletID = i;
	}

	Position = Init.Position;
	Rotation = Init.Rotation;
	Velocity = Init.Velocity;
	Scale = Vector3(1, 1, 1);
	DrawTexture = Init.DrawTexture;
	if (Init.offsetdirection == "Left")
	{
		Vector3 Left = VectorCrossProduct(Vector3(0, 1, 0), Init.ForwardDirection);
		Left *1.5f;
		Position -=  Left;
	}
	if (Init.offsetdirection == "Right")
	{
		Vector3 Right = VectorCrossProduct(Vector3(0, 1, 0), Init.ForwardDirection);
		Right *1.5f;
		Position += Right;
	}
}
void Gun::Setup(GameObjectInit Init)
{
	Position = Init.position;
	Rotation = Init.rotation;
	Scale = Init.scale;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
}

bool Gun::Fire()
{
	for (int i = 0; i < 50; i++)
	{
		if (objbulletlist[i].Alive == false)
		{	
			bulletInit TempBullet;
			TempBullet.DrawTexture = DrawTexture;;
			TempBullet.GunPos = Position;
			TempBullet.GunRot = Rotation;
			objbulletlist[i].MinPoints = MinPoints;
			objbulletlist[i].MaxPoints = MaxPoints;
			objbulletlist[i].Setup(TempBullet);
			objbulletlist[i].Alive = true;
			objbulletlist[i].TimeOutDestructor = 0;
			i = 60;
			return true;
		}

	}
	return false;
}
void Gun::Update()
{
		BulletWait += DeltaTime;
 	for (int i = 0; i < 50; i++)
	{
		if (objbulletlist[i].Alive == true)
		{
			objbulletlist[i].Update();
			objbulletlist[i].DeltaTime = DeltaTime;
			if (objbulletlist[i].TimeOutDestructor >= 5)
			{
				objbulletlist[i].Alive = false;
			}

		}
	}
	
}
Gun::~Gun()
{
}