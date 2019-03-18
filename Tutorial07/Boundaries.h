//File Name : Boundaries.h
#pragma once
#include "Target.h"
 struct BoundariesInit
{
	Vector3 Position, Rotation, Scale;
	float colourR, colourG, colourB;
	int targetchance, turretchance;
	bool leftWall, rightWall, frontwall, backwall, roof,floor;
	ID3D11ShaderResourceView * DrawTexture;
	ID3D11ShaderResourceView * TurretTexture;
	ID3D11ShaderResourceView *TargetTexture;
};
class Boundaries : public Target
{
public:
	GameObject Boundary;
	int targetchance, turretchance;
	bool FrontWall;
	bool BackWall;
	bool LeftWall;
	bool RightWall;
	bool Roof;
	bool Floor;
	bool TARGET;
	bool TURRET;
	GameObject objLeftWall;
	GameObject objRightWall;
	GameObject objFrontWall;
	GameObject objBackWall;
	GameObject objRoof;
	GameObject objFloor;
	Target objTarget;
	Boundaries();
	void Setup(BoundariesInit Init);
	void Setup(GameObjectInit Init) override;
	void Update() override;
	//void SpawnTarget();
	//void SpawnTurret();

	~Boundaries();
};