#include "Transformation.h"



Transformation::Transformation()
{
	Position = XMFLOAT3	(0,0,0);
	Rotation = XMFLOAT3(0, 0, 0);
	Scale = XMFLOAT3(1, 1, 1);
	Red = 1;
	Green = 1;
	Blue = 1;
	Lock = false;
	//Draw();
}
void Transformation::Setup(
	XMFLOAT3 position,
	XMFLOAT3 rotation,
	XMFLOAT3 scale,
	float colourR,
	float colourG,
	float colourB)
{
	Position = position;
	Rotation = rotation;
	Scale = scale;
	Red = colourR;
	Green = colourG;
	Blue = colourB;


}

void Transformation::Update()
{
	CollisionBox.Min = VectorSub(Position, Scale);
	CollisionBox.Max = Vectoradd(Position, Scale);
}
Transformation::~Transformation()
{
}
