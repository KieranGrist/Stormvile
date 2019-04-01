#include "Boundaries.h"



Boundaries::Boundaries()
{
}


void Boundaries::Setup(BoundariesInit Init)
{

	GameObjectInit Temp;
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	Temp.DrawTexture = Init.DrawTexture;
	Setup(Temp);
	LeftWall = Init.leftWall;
	RightWall = Init.rightWall;
	BackWall = Init.backwall;
	FrontWall = Init.frontwall;
	Roof = Init.roof;
	Floor = Init.floor;
	turretchance = Init.turretchance;
	targetchance = Init.targetchance;
	if (BackWall == true)
	{

		Temp.position = Vector3(Position.x - 5.5f, Position.y + 5.5f, Position.z);
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
		Temp.scale = Vector3(0.5, 5, 5);
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;
		objBackWall.Setup(Temp);
	}
	if (FrontWall == true)
	{
		Temp.position = Vector3(Position.x + 5.5f, Position.y + 5.5f, Position.z);
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
		Temp.scale = Vector3(0.5, 5, 5);
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;
		objFrontWall.Setup(Temp);
	}
	if (LeftWall == true)
	{
		Temp.position = Vector3(Position.x, Position.y + 5.5f, Position.z + 5.5f);
		Temp.rotation = Vector3(0, 0, 0);
		Temp.scale = Vector3(5.0f, 5.0f, 0.5f);
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;
		objLeftWall.Setup(Temp);
	}
	if (RightWall == true)
	{
		Temp.position = Vector3(Position.x, Position.y + 5.5f, Position.z - 5.5f);
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
		Temp.scale = Vector3(5.0f, 5.0f, 0.5f);
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;
		objRightWall.Setup(Temp);
	}
	if (Roof == true)
	{
		Temp.position = Vector3(Position.x, Position.y + 10.5f, Position.z);
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
		Temp.scale = Vector3(5.0f, 0.5f, 5.0f);
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;
		objRoof.Setup(Temp);
	}
	if (Floor == true)
	{
		Temp.position = Vector3(Position.x, Position.y, Position.z);
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
		Temp.scale = Vector3(5.0f, 0.5f, 5.0f);
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;
		objFloor.Setup(Temp);
	}
	bool TargetSpawned = false;
	int RandomNumber = rand() % 100;
	int TimesRan = 0;

	if (RandomNumber <= targetchance)
	{
		while (TargetSpawned == false)
		{
			TimesRan++;
			if (TimesRan >= 1000)
			{
				TargetSpawned = true;
			}
			int Wall = rand() % 6;
			switch (Wall)
			{
			case 0:
				if (Floor == true)
				{
					targetInit TargetTemp;
					TargetTemp.Position = objFloor.Position;
					TargetTemp.Position.y += 1.5f;
					TargetTemp.Rotation = Vector3(0, 0, 0);
					TargetTemp.Scale = Vector3(1, 1, 1);
					TargetTemp.Health = 100;
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;
					TargetTemp.DrawTexture = Init.TargetTexture;
					TARGET = true;
					objTarget.Setup(TargetTemp);
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 1:
				if (Roof == true)
				{
					targetInit TargetTemp;
					TargetTemp.Position = objRoof.Position;
					TargetTemp.Position.y -= 1.5f;
					TargetTemp.Rotation = Vector3(0, 0, 0);
					TargetTemp.Scale = Vector3(1, 1, 1);
					TargetTemp.Health = 100;
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;
					TargetTemp.DrawTexture = Init.TargetTexture;
					TARGET = true;
					objTarget.Setup(TargetTemp);
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 2:
				if (LeftWall == true)
				{
					targetInit TargetTemp;
					TargetTemp.Position = objLeftWall.Position;
					TargetTemp.Position.z -= 1.5f;
					TargetTemp.Rotation = Vector3(0, 0, 0);
					TargetTemp.Scale = Vector3(1, 1, 1);
					TargetTemp.Health = 100;
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;
					TargetTemp.DrawTexture = Init.TargetTexture;
					TARGET = true;
					objTarget.Setup(TargetTemp);
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 3:
				if (RightWall == true)
				{
					targetInit TargetTemp;
					TargetTemp.Position = objRightWall.Position;
					TargetTemp.Position.z += 1.5f;
					TargetTemp.Rotation = Vector3(0, 0, 0);
					TargetTemp.Scale = Vector3(1, 1, 1);
					TargetTemp.Health = 100;
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;
					TargetTemp.DrawTexture = Init.TargetTexture;
					TARGET = true;
					objTarget.Setup(TargetTemp);
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 4:
				if (FrontWall == true)
				{
					targetInit TargetTemp;
					TargetTemp.Position = objFrontWall.Position;
					TargetTemp.Position.x -= 1.5f;
					TargetTemp.Rotation = Vector3(0, 0, 0);
					TargetTemp.Scale = Vector3(1, 1, 1);
					TargetTemp.Health = 100;
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;
					TargetTemp.DrawTexture = Init.TargetTexture;
					TARGET = true;
					objTarget.Setup(TargetTemp);
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 5:
				if (BackWall == true)
				{
					targetInit TargetTemp;
					TargetTemp.Position = objBackWall.Position;
					TargetTemp.Position.x += 1.5f;
					TargetTemp.Rotation = Vector3(0, 0, 0);
					TargetTemp.Scale = Vector3(1, 1, 1);
					TargetTemp.Health = 100;
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;
					TargetTemp.DrawTexture = Init.TargetTexture;
					TARGET = true;
					objTarget.Setup(TargetTemp);
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			default:
				TargetSpawned = false;
				break;

			}
		}
	}
	if (turretchance <= RandomNumber)
	{

	}


	if (BackWall == true)
	{
		objBackWall.MinExtent = VectorSub(objBackWall.Position, Vector3(0.5, 5, 5));
		objBackWall.MaxExtent = VectorAdd(objBackWall.Position, Vector3(0.5, 5, 5));


	}
	if (FrontWall == true)
	{
		objFrontWall.MinExtent = VectorSub(objFrontWall.Position, Vector3(0.5, 5, 5));
		objFrontWall.MaxExtent = VectorAdd(objFrontWall.Position, Vector3(0.5, 5, 5));

	}
	if (LeftWall == true)
	{
		objLeftWall.MinExtent = VectorSub(objLeftWall.Position, Vector3(5.0f, 5.0f, 0.5f));
		objLeftWall.MaxExtent = VectorAdd(objLeftWall.Position, Vector3(5.0f, 5.0f, 0.5f));
	}
	if (RightWall == true)
	{
		objRightWall.MinExtent = VectorSub(objRightWall.Position, Vector3(5.0f, 5.0f, 0.5f));
		objRightWall.MaxExtent = VectorAdd(objRightWall.Position, Vector3(5.0f, 5.0f, 0.5f));
	}
	if (Roof == true)
	{
		objRoof.MinExtent = VectorSub(objRoof.Position, Vector3(5.0f, 0.5f, 5.0f));
		objRoof.MaxExtent = VectorAdd(objRoof.Position, Vector3(5.0f, 0.5f, 5.0f));
	}
	if (Floor == true)
	{
		objFloor.MinExtent = VectorSub(objFloor.Position, Vector3(5.0f, 0.5f, 5.0f));
		objFloor.MaxExtent = VectorAdd(objFloor.Position, Vector3(5.0f, 0.5f, 5.0f));
	}

}
	

void Boundaries::Setup(GameObjectInit Init) {
	Position = Init.position;
	Red = Init.ColourR;
	Blue = Init.ColourB;
	Green = Init.ColourG;
	DrawTexture = Init.DrawTexture;
	Rotation = Init.rotation;
	Scale = Init.scale;
}



void Boundaries::Update()
{

	if (BackWall == true)
	{
		objBackWall.Update();	
	}
	if (FrontWall == true)
	{
		objFrontWall.Update();
	}
	if (LeftWall == true)
	{
		objLeftWall.Update();
	}
	if (RightWall == true)
	{
		objRightWall.Update();
	}
	if (Roof == true)
	{
		objRoof.Update();
	}
	if (Floor == true)
	{
		objFloor.Update();
	}
	if (TARGET == true)
	{
		if (objTarget.Health <= 0)
		{
			TARGET = false;
		}
		objTarget.Update();
	}
}
Boundaries::~Boundaries()
{
}