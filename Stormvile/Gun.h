//File Name : Gun.h
#pragma once
#include "Bullet.h"	

//Init Structure for gun setup
struct initGun
{  
	Vector3 ForwardDirection; //Foward Direction 
	Vector3	Position; //Origin Postion
	Vector3	Rotation; //Origin Rotation
	string offsetdirection; //Determines what side of the player the gun is
	ID3D11ShaderResourceView * DrawTexture; //Draw texture of gun
};

//Gun Class used to store and fire bullets 
class Gun : Bullet
{
public:
	float BulletWait =0; //Wait timer for firring bullets in a pattern
	Bullet *objbulletlist; // = new Bullet[50];
	ID3D11ShaderResourceView * DrawTexture; //Draw texture
	float DeltaTime; //Physics Delta Time 
	Gun();
	void Setup(initGun Init); //Forward decleration of setup
	void Setup(GameObjectInit Init) override; //Overide gameobject setup
	bool Fire(); //Forward decleration Of fire
	void Update() override; //Override of update
	~Gun();
};

