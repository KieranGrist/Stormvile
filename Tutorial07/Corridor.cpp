#include "Corridor.h"



Corridor::Corridor()
{
	objFloors = new Boundaries[50];
}
void Corridor::Reset()
{
	//Setup(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), 0, 0, 0, 2, "Forward");
}
void Corridor::Setup(corridorsInit Init)
{

	GameObjectInit Temp;
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	Temp.DrawTexture = Init.DrawTexture;
    GameObject::Setup(Temp);
	int RandomNumber = 25;
	int RandomNumber2 = rand() % 50;;
	if (Init.floorLength > 50)
	{
		Init.floorLength = 50;
	}
	for (int i = 0; i < FloorLength; i++)
	{
		objFloors[i].TARGET = false;
	}
	FloorLength = Init.floorLength;
//All Corridors Start from the ation position and then create in the intended direction
	if (Init.CorridorDirection == "Down")
	{
		for (int i = 0; i < FloorLength; i++)
		{
			if (i == 0)
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
			    corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture; 
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
		 else if (i == FloorLength -1)
			{
				BoundariesInit corridortemp;
				corridortemp.targetchance = RandomNumber;
				 corridortemp.turretchance= RandomNumber2;
				corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[i - 1].Position.y - 10.0f, objFloors[0].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			else
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[i - 1].Position.y - 10.0f, objFloors[0].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = true;
				corridortemp.backwall = true;
				corridortemp.floor = false;
				corridortemp.roof = false;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
		}
	}
	if (Init.CorridorDirection == "Up"	)
	{
		for (int i = 0; i < FloorLength; i++)
		{
			if (i == 0)
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			  else if (i == FloorLength -1)
			{
				BoundariesInit corridortemp;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[i - 1].Position.y + 10.0f, objFloors[0].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			else
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[i-1].Position.y+10.0f, objFloors[0].Position.z );
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = true;
				corridortemp.backwall = true;
				corridortemp.floor = false;
				corridortemp.roof = false;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
		}
	}
	if (Init.CorridorDirection == "Right")
	{
		for (int i = 0; i < FloorLength; i++)
		{
			if (i == 0)
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			  else if (i == FloorLength -1)
			{
				BoundariesInit corridortemp;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[0].Position.y, objFloors[i - 1].Position.z - 10.0f);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			else
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[0].Position.y, objFloors[i - 1].Position.z - 10.0f);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = false;
				corridortemp.rightWall = false;
				corridortemp.frontwall = true;
				corridortemp.backwall = true;
				corridortemp.floor = true;
				corridortemp.roof = true;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
		}
	}
	if (Init.CorridorDirection == "Left")
	{
		for (int i = 0; i < FloorLength; i++)
		{
				if (i == 0)
				{
					BoundariesInit corridortemp;
					corridortemp.Position = Vector3(Position.x, Position.y, Position.z );
					corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
					corridortemp.Scale = Vector3(5, 0.5, 5);
					corridortemp.colourR = Init.colourR;
					corridortemp.colourG = Init.colourG;
					corridortemp.colourB = Init.colourB;
					corridortemp.targetchance = RandomNumber;
					   corridortemp.turretchance= RandomNumber2;
					corridortemp.leftWall = Init.FirstBlock.leftWall;
					corridortemp.rightWall = Init.FirstBlock.rightWall;
					corridortemp.frontwall = Init.FirstBlock.frontwall;
					corridortemp.backwall = Init.FirstBlock.backwall;
					corridortemp.floor = Init.FirstBlock.floor;
					corridortemp.roof = Init.FirstBlock.roof;
					corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
					objFloors[i].Setup(corridortemp);
				}
				  else if (i == FloorLength -1)
				{
					BoundariesInit corridortemp;
					corridortemp.targetchance = RandomNumber;
					   corridortemp.turretchance= RandomNumber2;
					corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[0].Position.y, objFloors[i - 1].Position.z + 10.0f);
					corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
					corridortemp.Scale = Vector3(5, 0.5, 5);
					corridortemp.colourR = Init.colourR;
					corridortemp.colourG = Init.colourG;
					corridortemp.colourB = Init.colourB;
					corridortemp.leftWall = Init.LastBlock.leftWall;
					corridortemp.rightWall = Init.LastBlock.rightWall;
					corridortemp.frontwall = Init.LastBlock.frontwall;
					corridortemp.backwall = Init.LastBlock.backwall;
					corridortemp.floor = Init.LastBlock.floor;
					corridortemp.roof = Init.LastBlock.roof;
					corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
					objFloors[i].Setup(corridortemp);
				}
				else
				{
					BoundariesInit corridortemp;
					corridortemp.Position = Vector3(objFloors[0].Position.x, objFloors[0].Position.y, objFloors[i - 1].Position.z+10.0f);
					corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
					corridortemp.Scale = Vector3(5, 0.5, 5);
					corridortemp.colourR = Init.colourR;
					corridortemp.colourG = Init.colourG;
					corridortemp.colourB = Init.colourB;
					corridortemp.targetchance = RandomNumber;
					 corridortemp.turretchance= RandomNumber2;
					corridortemp.leftWall = false;
					corridortemp.rightWall = false;
					corridortemp.frontwall = true;
					corridortemp.backwall = true;
					corridortemp.floor = true;
					corridortemp.roof = true;
					corridortemp.DrawTexture = Init.DrawTexture;  
					corridortemp.TargetTexture = Init.TargetTexture;
					objFloors[i].Setup(corridortemp);
				}
			}
		}
	if (Init.CorridorDirection == "Backward")
	{
		for (int i = 0; i < FloorLength; i++)
		{
			if (i == 0)
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y,Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			  else if (i == FloorLength -1)
			{
				BoundariesInit corridortemp;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.Position = Vector3(objFloors[i - 1].Position.x - 10.0f, objFloors[i - 1].Position.y, objFloors[i - 1].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			else
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(objFloors[i - 1].Position.x - 10.0f, objFloors[i - 1].Position.y, objFloors[i - 1].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y,Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				   corridortemp.turretchance= RandomNumber2;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = false;
				corridortemp.backwall = false;
				corridortemp.floor = true;
				corridortemp.roof = true;
				objFloors[i].Setup(corridortemp);
			}
		}
	}
	if (Init.CorridorDirection == "Forward")
	{
		for (int i = 0; i < FloorLength; i++)
		{
			if (i == 0)
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x,Rotation.y,Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance= RandomNumber2;
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			  else if (i == FloorLength -1)
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(objFloors[i - 1].Position.x + 10.0f, objFloors[i - 1].Position.y, objFloors[i - 1].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.targetchance = RandomNumber;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;
				corridortemp.DrawTexture = Init.DrawTexture;  corridortemp.TargetTexture = Init.TargetTexture;
				objFloors[i].Setup(corridortemp);
			}
			else
			{
				BoundariesInit corridortemp;
				corridortemp.Position = Vector3(objFloors[i - 1].Position.x + 10.0f, objFloors[i - 1].Position.y, objFloors[i - 1].Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				corridortemp.targetchance = RandomNumber;
				corridortemp.DrawTexture = Init.DrawTexture;  
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = false;
				corridortemp.backwall = false;
				corridortemp.floor = true;
				corridortemp.roof = true;
				objFloors[i].Setup(corridortemp);
			}
		}
	}
}
void Corridor::Setup(GameObjectInit Init)
{
}
void Corridor::Update()
{
	for (int i = 0; i < FloorLength; i++)
	{
		objFloors[i].Update();

	}
}

Corridor::~Corridor()
{
}
