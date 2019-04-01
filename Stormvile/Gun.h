//File Name : Gun.h

#pragma once
#include "Bullet.h"	
struct initGun
{
   
	Vector3 ForwardDirection,Position,Rotation,Velocity;
	string offsetdirection;
	ID3D11ShaderResourceView * DrawTexture;
};
class Gun : public Bullet
{
public:
	float BulletWait =0;
	Bullet *objbulletlist; // = new Bullet[50];
	ID3D11ShaderResourceView * DrawTexture;
	float DeltaTime;
	Gun();
	void Setup(initGun Init);
	void Setup(GameObjectInit Init) override;
	bool Fire();
	void Update() override;
	~Gun();
};

