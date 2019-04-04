//File Name : Corridor.h
#pragma once
#include "Boundaries.h"

//Initialise structure to be used for Corridor Setup
struct corridorsInit
{
	Vector3 Position; //Origin Postion
	Vector3 Rotation; //Origin Rotation
	Vector3 Scale; //Origin Scale

	float colourR; //Red
	float colourG; //Green
	float colourB; //Blue

	int floorLength; //Length Of corridor, Clamps from 2 to 50

	string CorridorDirection; //Direction Of Corridor,E.g. "Forward"

	ID3D11ShaderResourceView * DrawTexture; //Corridor texture
	ID3D11ShaderResourceView * TurretTexture; //Turret Texture
	ID3D11ShaderResourceView * TargetTexture; //Target TExture
	
	BoundariesInit FirstBlock; //Bound Init to be used to set bound[0] wall bools
	BoundariesInit LastBlock; //Bound Init to be used to set bound[Length -1] wall bools

};

//Corridor Class, this allows you to create a corridor from a point in worldspace and define the direction it goes
class Corridor : public Boundaries
{
public:
	int FloorLength; //How Long the Corridor is in boundarie blocks
	Boundaries * objBoundaries; //Array Of Boundaries
	Corridor();
	void Setup(corridorsInit Init); //Forward decleration of Corridors Setup
	void Setup(GameObjectInit Init) override; //Override of Game Object Setup
	void Update() override; //Override of Game Object Update
	~Corridor();
};

