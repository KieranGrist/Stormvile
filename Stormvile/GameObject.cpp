#include "GameObject.h"




GameObject::GameObject()
{
	Position = Vector3	(0,0,0);
	Rotation = Vector3(0, 0, 0);
	Scale = Vector3(1, 1, 1);
	Red = 1;
	Green = 1;
	Blue = 1;
	Lock = false;
}

void GameObject::Setup(
	GameObjectInit Init)
{
	Position = Init.position;
	Rotation = Init.rotation;
	Scale = Init.scale;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
}

void GameObject::Update()
{
	MinExtent = VectorSub(Position, MinPoints);
	MaxExtent = VectorAdd(Position, MaxPoints);
	Draw();
}
GameObject::~GameObject()
{
}
