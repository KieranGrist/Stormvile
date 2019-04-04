#include "Target.h"

//Target Constructor
Target::Target()
{
	Health = 0;
}


//Target Setup
void Target::Setup(targetInit Init)
{
	//Initiilise Targets Game Object With the structure values
	GameObjectInit Temp;
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	Temp.DrawTexture = Init.DrawTexture;
	Setup(Temp);
	Health = Init.Health;
	
}
//Gameobject setup
void Target::Setup(GameObjectInit Init)
{
	//Initiilise Targets Game Object With the structure values
	Position = Init.position;
	Scale = Init.scale;
	Rotation = Init.rotation;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
	Health = 100;
}
//Update Target
void Target::Update()
{
	//Simple Update script, it will only draw and update collision if the health is more then 1
	if (Health >= 1)
	{
		//Set aabbb
		MinExtent = VectorSub(Position, Vector3(1,1,1));
		MaxExtent = VectorAdd(Position, Vector3(1,1,1));

		//Draw Target
		Draw();
	}
	else
	{
	}
}

Target::~Target()
{
}
