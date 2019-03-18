//File Name : Corridor.h

#pragma once
#include "Boundaries.h"
struct corridorsInit
{
	Vector3 Position, Rotation, Scale;
	float colourR , colourG , colourB;
	int floorLength;
	string CorridorDirection;
	ID3D11ShaderResourceView * DrawTexture;
	ID3D11ShaderResourceView * TurretTexture;
	ID3D11ShaderResourceView * TargetTexture;
	BoundariesInit FirstBlock,LastBlock;

};
class Corridor :public Boundaries
{
public:
	int FloorLength;
	Boundaries * objFloors;
	//How many floors long is the corridor
	Corridor();
	void Reset();
	void Setup(corridorsInit Init);
	void Setup(GameObjectInit Init) override;
	void Update() override;
	~Corridor();
};

