#pragma once
#include "Boundaries.h"
struct roomInit
{
	Vector3 Position, Rotation, Scale;
	float colourR, colourG, colourB;
	int RoomSize;
	int targetchance, turretchance;
	bool leftWall, rightWall, frontwall, backwall, roof, floor;
	ID3D11ShaderResourceView * DrawTexture;
	ID3D11ShaderResourceView * TurretTexture;
	ID3D11ShaderResourceView *TargetTexture;
};
class Room :public Boundaries
{
public:
	int FloorLength;
	Room();
	void Setup(roomInit Init);
	void Setup(GameObjectInit Init) override;
	void Update() override;
	~Room();
	bool FrontWall;
	bool BackWall;
	bool LeftWall;
	bool RightWall;
	bool Roof;
	bool Floor;
	GameObject objLeftWall;
	GameObject objRightWall;
	GameObject objFrontWall;
	GameObject objBackWall;
	GameObject objRoof;
	GameObject objFloor;
};

