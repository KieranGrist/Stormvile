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
private:
	Vector3 RightDirecton, UpDirection, Velocity, Acceleration;
	float Mass, PITCH, YAW, Sensertivity =1;
public:
	float Health, DeltaTime;
	Gun objGunLeft,objGunRight;
	Vector3 Force;
	Vector3 ForwardDirection;
	int Shots;
	bool W, A, S, D, Q, E,LEFT,RIGHT,UP,DOWN, SHIFT, CONTROL,SPACE,X,PLUS,MINUS,F;
	ID3D11ShaderResourceView * DrawTexture;
	void Update() override;
	Player();
	void Setup(playerInit Init);
	void Setup(GameObjectInit Init) override;
	void Draw() override;
	~Player();
};