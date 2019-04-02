#pragma once
#include "GameObject.h"
struct targetInit
{
	Vector3 Position, Rotation, Scale;
	float colourR, colourG, colourB, Health;
	ID3D11ShaderResourceView * DrawTexture;
};
class Target: public GameObject
{
public:
	float Health =0; //Target Health
	void Setup(targetInit Init); //Setup target using Target initialise structure
	void Setup(GameObjectInit Init) override; //Setup Target as a gameobject overridden 
	void Update() override; //Overrided update function
	Target();
	~Target();
};

