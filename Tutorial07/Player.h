//File Name : Player.h
#pragma once

#include "GameObject.h"
#include "Gun.h"
struct playerInit
{
	Vector3 Position, Rotation, Scale;
	float colourR, colourG, colourB;
	float Health;
	int Shots;
	ID3D11ShaderResourceView * DrawTexture;
};
class Player : public GameObject
{
public:
	Gun objGunLeft,objGunRight;
	Vector3  Force, Acceleration, Velocity;
	Vector3 ForwardDirection, RightDirecton,UpDirection;
	float Mass, PITCH, YAW, Health, Sensertivity = 0.05f;
	int Shots;
	bool W, A, S, D, Q, E,LEFT,RIGHT,UP,DOWN, SHIFT, CONTROL,SPACE,X,PLUS,MINUS,F;
	ID3D11ShaderResourceView * DrawTexture;
	void Update() override;
	Player();
	void Setup(playerInit Init);
	void Setup(GameObjectInit Init) override;
	~Player();
};