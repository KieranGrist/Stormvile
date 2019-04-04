//File Name : Player.h
#pragma once

#include "GameObject.h"
#include "Gun.h"

//Init structure for player 
struct playerInit
{
	Vector3 Position; //Player Position 
		Vector3 Rotation; //Player Rotation 
		Vector3	Scale; //Player Scale 
		float colourR; //Player Red Colour
		float colourG; //Player Green Colour
		float colourB; //Player Blue Colour 
	float Health; //Player Health
	int Shots; //Player Shots
	ID3D11ShaderResourceView * DrawTexture; //Player draw texture
};

//Player class used for any entity that can play the game
class Player : public GameObject
{
public:
	Vector3 ForwardDirection; //Direction Player is facing
	Vector3 RightDirecton;  //Direction to the right of forward direction 
	Vector3 UpDirection; //Up direction from the two previous direction
	Vector3 Velocity; //Phyiscal Velocity
	Vector3 Acceleration; //Physical Acceleration
	Vector3 Force; //Applies Physical Force to object
	Vector3 MODELMINPOINT; //Models Minum Point  
	Vector3 MODELMAXPOINT; //Models Maxium Point
	float  Mass; //Player Mass
	float PITCH; //Rotation X
	float YAW;  //Rotation Y
	float Sensertivity = 0.7; //How quickly a player turns 
	float Health; //Health Of Players
	float DeltaTime; //Physical Delta Time
	Gun objGunLeft; //Left gun
	Gun	objGunRight; //Right Gun
	int Shots; //Shots fired

	//Keycode
	bool W, A, S, D, Q, E,LEFT,RIGHT,UP,DOWN, SHIFT, CONTROL,SPACE,X,PLUS,MINUS,F;


	ID3D11ShaderResourceView * DrawTexture; //Draw Texure
	Player();
	void Setup(playerInit Init);  //Forward decleration of player setup
	void Setup(GameObjectInit Init) override; //Override of gameobject setup
	void Update() override; //Override of update
	void Draw() override; //Overide of draw
	~Player();
};