#include "Corridor.h"



Corridor::Corridor()
{
}
void Corridor::Reset()
{
	Setup(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), 0, 0, 0, 2, "Forward");
}
void Corridor::Setup(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale, float colourR, float colourG, float colourB, int floorLength, string CorridorDirection)
{

	transform.Setup(position, rotation, scale, colourR, colourG, colourB);
	if (floorLength > 50)
	{
		floorLength = 50;
	}
	FloorLength = floorLength;

	//	Setup(XMFLOAT3 Position, XMFLOAT3 Rotation, XMFLOAT3 Scale, float colourR, float colourG, float colourB, int targetchance, bool leftWall, bool rightWall, bool frontwall, bool backwall, bool roof)

	if (CorridorDirection == "Forward")
	{
		for (int i = 0; i < FloorLength; i++)
		{
			if (i == 0)
				objFloors[i].Setup(XMFLOAT3(transform.Position.x, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(5, 0.5, 5), colourR, colourG, colourB, 0, true, true, false, false, true);
			else
				objFloors[i].Setup(XMFLOAT3(objFloors[i - 1].transform.Position.x + 10.0f, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(5, 0.5, 5), colourR, colourG, colourB, 0, true, true, false, false, true);
		}
		objFloors[0].BackWall = false;
		objFloors[FloorLength - 1].FrontWall = false;
	}


	//objFloors[0].
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
