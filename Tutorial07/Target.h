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
	float Health =0;
	void Setup(targetInit Init);
	void Setup(GameObjectInit Init) override;
	void Update() override;
	Target();
	~Target();
};

