#include "GameObject.h"
//Gameobject constructor
GameObject::GameObject()
{
	Position = Vector3(0,0,0);
	Rotation = Vector3(0, 0, 0);
	Scale = Vector3(1, 1, 1);
	Red = 1;
	Green = 1;
	Blue = 1;
     DrawTexture = nullptr; 
}

//Setup game object
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
//Gameobject Update
void GameObject::Update()
{
	//Set Min extent
	MinExtent = VectorSub(Position, Vector3(1, 1, 1));

	//Set Max Extent
	MaxExtent = VectorAdd(Position, Vector3(1, 1, 1));

	//Draw object
	Draw();
}
GameObject::~GameObject()
{
	Red = NULL;
	Green = NULL;
	Blue = NULL;
	DrawTexture = nullptr;
}
