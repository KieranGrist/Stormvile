//File Name : Bullet.h

#pragma once
#include "GameObject.h"
struct bulletInit
{
	Vector3 GunPos,  GunRot;
	ID3D11ShaderResourceView * DrawTexture;
};

class Bullet : public GameObject
{
	
public:
	float TimeOutDestructor;
	Vector3  Force, Acceleration, Velocity;
	Vector3 ForwardDirection;
	float Pitch, Yaw,Mass;
	bool Alive = false;
	float DeltaTime;
	int GridID;
	int BulletID =0;
	Bullet();
	void Setup(GameObjectInit Init) override;
	void Setup(bulletInit Init);
	void Update() override;
	~Bullet();
private:

};

