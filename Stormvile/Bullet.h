//File Name : Bullet.h
#pragma once
#include "GameObject.h"

//Initialise structure to be used for Bullet setup
struct bulletInit
{

	Vector3 GunPos; //Gun Positon
	Vector3	GunRot; //Gun Rotation

	//Bullet Draw TExture
	ID3D11ShaderResourceView * DrawTexture;
};

//Bullet class, this class fires and updates bullets
class Bullet : public GameObject
{
public:
	float TimeOutDestructor; //Bullet timeout
	Vector3 Force; //Physic Force to be applied to a bullet
	Vector3	Acceleration; //Acceleration of bullet
	Vector3 Velocity; //Velocity of bullet
	Vector3 ForwardDirection; //Forward direction of bullet
	float Pitch; //Rotational Pitch
	float Yaw; //Rotatonal Yaw
	float Mass; //Mass
	bool Alive = false; //Variable to check if bullet is alive
	float DeltaTime; //Delta time
	int BulletID =0; //Bullet ID mainly used for debuging
	Bullet();
	void Setup(bulletInit Init);  //Setup Bullet
	void Update() override; //Override of Gameobject update
	~Bullet();
};

