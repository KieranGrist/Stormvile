//File Name : Gun.h

#pragma once
#include "Bullet.h"	
struct initGun
{
   
	Vector3 ForwardDirection,Position,Rotation,Velocity;
	string offsetdirection;
	ID3D11ShaderResourceView * DrawTexture;
};
class Gun : Bullet
{
public:
	float BulletWait =0;
	Bullet *objbulletlist; // = new Bullet[50];
	ID3D11ShaderResourceView * DrawTexture;
	Gun();
	void Setup(initGun Init);
	void Setup(GameObjectInit Init) override;
	void Fire();
	void Update() override;
	~Gun();
};

