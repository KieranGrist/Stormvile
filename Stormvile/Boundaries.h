//File Name : Boundaries.h
#pragma once
#include "Target.h"


//Initialise struct used for Boundary setup
 struct BoundariesInit
{
	

	 Vector3 Position; //Origin Position
	 Vector3 Rotation; //Origin Rotation
	 Vector3 Scale; //Origin Scale
	  
	 float colourR; //Red
	 float colourG; //Green
	 float colourB; //Blue


	 int targetchance; //Chance To spawn a target
	 int turretchance; //Chance to spawn a turret

	 bool leftWall; //Does Left Wall Exist
	 bool rightWall; //Does Right Wall Exist
	 bool frontwall; //Does Front Wall Exist
	 bool backwall; //Does Back Wall Exist
	 bool roof; //Does Roof Exist
	 bool floor; //Does Floor Exist

	
	ID3D11ShaderResourceView * DrawTexture; //Texture for game object to be drawn with
	ID3D11ShaderResourceView * TurretTexture; 	//Texture for Turret to be drawn with
	ID3D11ShaderResourceView *TargetTexture; //Texture for target to be drawn with
};

//Boundaries class, this class allows you to create an object with a roof, floor and walls surronding it, 10,10,10 in scale
class Boundaries : public Target
{

public:

	bool TURRET; //bool to check if there is a turret
	int turretchance; //int to check turret chance 
	Target objTarget; //Precreating target to be initialised in cpp 

	int targetchance; //int to check target chance
	bool FrontWall; //Set to true if Front wall needs to be drawn
	bool BackWall; //Set to true if Back wall needs to be drawn
	bool LeftWall; //Set to true if Left wall needs to be drawn
	bool RightWall;//Set to true if Right wall needs to be drawn
	bool Roof; //Set to true if Roof needs to be drawn
	bool Floor; //Set to true if floor needs to be drawn
	bool TARGET; //Set to true if there is a turret
	GameObject objLeftWall; //Game Object For Left Wall
	GameObject objRightWall; //Game Object For Right Wall
	GameObject objFrontWall; //Game Object For Front Wall
	GameObject objBackWall; //Game Object For Back Wall
	GameObject objRoof; //Game Object for roof
	GameObject objFloor; //Game Object for Floor

	Boundaries();
	void Setup(BoundariesInit Init); //Forward decleration of Boundaries Set up
	void Setup(GameObjectInit Init) override; //Override of Game Object Setup
	void Update() override; //Override of Game Object Update
	~Boundaries();
};