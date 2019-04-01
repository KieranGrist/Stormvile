//File Name : GameObject.h
#pragma once
#include "Model.h"
struct GameObjectInit
{
	Vector3 position, rotation, scale; float ColourR, ColourG, ColourB;
	ID3D11ShaderResourceView * DrawTexture;
};
class GameObject :public Model
{
public:
	Vector3 MinPoints, MaxPoints;
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
	
	virtual void ModelDraw();//Moderfied Draw call for drawing imported models
};

