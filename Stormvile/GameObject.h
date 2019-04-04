//File Name : GameObject.h
#pragma once
#include "CollisionBox.h"

//Init Structure for game object setup
struct GameObjectInit
{
	Vector3 position; //GameObject Postion
	Vector3 rotation; //GameObject Rotation
	Vector3 scale; //GameObject Scale

	float ColourR; //Red
	float ColourG; //Green
	float ColourB; //Blue
	ID3D11ShaderResourceView * DrawTexture;
};

//Game Object Class, Used to move and draw objects in game world
class GameObject :public CollisionBox
{
public:
	Vector3 Position; //Position in the world
	Vector3 Rotation; //Rotation in the world
	Vector3 Scale; //Scale in the world
	float Red; //Defines the Ammount of red 
	float Green; //Defines the ammount of green
	float Blue; //Defines the amount of Blue
	ID3D11ShaderResourceView * DrawTexture; //Draw Texture
	GameObject();
	virtual void Setup(GameObjectInit Init); //Forward decleration of Setup
	virtual void Update(); //Forward Decleration of Update
	virtual void Draw(); //Forward Decleration of Draw
	~GameObject();

};

