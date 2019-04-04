#pragma once
#include "GameObject.h"
struct targetInit
{
	Vector3 Position; //Player Position 
	Vector3 Rotation; //Player Rotation 
	Vector3	Scale; //Player Scale 
	float colourR; //Player Red Colour
	float colourG; //Player Green Colour
	float colourB; //Player Blue Colour 
	float Health; //Player Health
	ID3D11ShaderResourceView * DrawTexture; //Draw texture
};
class Target: public GameObject
{
public:
	Vector3 mODELMINPOINT;
	Vector3 mODELMAXPOINT;
	float Health =0; //Target Health
	void Setup(targetInit Init); //Setup target using Target initialise structure
	void Setup(GameObjectInit Init) override; //Overrided setup 
	void Update() override; //Overrided update function
	//void Draw() override;
	Target();
	~Target();
};

