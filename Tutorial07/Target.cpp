#include "Target.h"



void Target::Setup(targetInit Init)
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
	Health = Init.Health;
	
}

void Target::Setup(GameObjectInit Init)
{
	Position = Init.position;
	Scale = Init.scale;
	Rotation = Init.rotation;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
}

void Target::Update()
{
	MinExtent = VectorSub(Position, Vector3(1,1,1));
	MaxExtent = VectorAdd(Position, Vector3(1, 1, 1));
	if (Health >= 1)
	{
		Draw();
	}
	else
	{
		Position.x += 500000.0f;
		Position.y += 500000.0f;
		Position.z += 500000.0f;
	}
}

Target::Target()
{
}


Target::~Target()
{
}
