//File Name : GameObject.h
#pragma once
#include "CollisionBox.h"
struct GameObjectInit
{
	Vector3 position, rotation, scale; float ColourR, ColourG, ColourB;
	ID3D11ShaderResourceView * DrawTexture;
};
class GameObject :public CollisionBox
{
public:
	Vector3 Position; //Position in the world
	Vector3 Rotation; //Rotation in the world
	Vector3 Scale; //Scale
	float Red;
	float Green;
	float Blue;
	bool Lock;
	ID3D11ShaderResourceView * DrawTexture;
	virtual void Update();
	GameObject();
	virtual void Setup(GameObjectInit Init);
	~GameObject();
	virtual void Draw();
};

