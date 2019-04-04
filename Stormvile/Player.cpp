#include "Player.h"


//Player Constructor
Player::Player()
{
	ForwardDirection = Vector3();
	 RightDirecton = Vector3();
	 UpDirection = Vector3();
	 Velocity = Vector3();
	 Acceleration = Vector3();
	 Force = Vector3();
	 MODELMINPOINT = Vector3();
	 MODELMAXPOINT = Vector3();
	 Mass = 1.01f;
	 PITCH =0.0f; 
	 YAW =0.0f; 
	 Sensertivity = 0.7; 
	 Health = 100.0f; 
	 DeltaTime = 0.0f; 
	 objGunLeft = Gun(); 
	 objGunRight = Gun();
	 Shots = 0; 
	 W = false;
	 A = false;
	 S = false;
	 D = false;
	 Q = false;
	 E = false;
	 LEFT = false;
	 RIGHT = false;
	 UP = false;
	 DOWN = false;
	 SHIFT = false;
	 CONTROL = false;
	 SPACE = false;
	 X = false;
	 PLUS = false;
	 MINUS = false;
	 F = false;


}

//Setup Function For Player
void Player::Setup(playerInit Init)
{
	//Setting Default Values
	ForwardDirection = Vector3();
	RightDirecton = Vector3();
	UpDirection = Vector3();
	Velocity = Vector3();
	Acceleration = Vector3();
	Force = Vector3();
	MODELMINPOINT = Vector3();
	MODELMAXPOINT = Vector3();
	Mass = 1.01f;
	PITCH = 0.0f;
	YAW = 0.0f;
	Sensertivity = 0.7;
	Health = 100.0f;
	DeltaTime = 0.0f;
	objGunLeft = Gun();
	objGunRight = Gun();
	Shots = 0;
	W = false;
	A = false;
	S = false;
	D = false;
	Q = false;
	E = false;
	LEFT = false;
	RIGHT = false;
	UP = false;
	DOWN = false;
	SHIFT = false;
	CONTROL = false;
	SPACE = false;
	X = false;
	PLUS = false;
	MINUS = false;
	F = false;




	ForwardDirection = Vector3(0, 0, 0);
	GameObjectInit Temp;
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	DrawTexture = Init.DrawTexture;
	Temp.DrawTexture = Init.DrawTexture;
	Setup(Temp);
	Health = Init.Health;
	Shots = Init.Shots;
	Velocity = Vector3(0, 0, 0);
	PITCH = Rotation.x;
	YAW = Rotation.y;

}

//Gameobject Setup
void Player::Setup(GameObjectInit Init)
{
	Position = Init.position;
	Scale = Init.scale;
	Rotation = Init.rotation;
	Blue = Init.ColourB;
	Green = Init.ColourG;
	Red = Init.ColourR;
	DrawTexture = Init.DrawTexture;
}

//Player Upadate
void Player::Update()
{
	//Forces scale to be 1,1,1,
	Scale = Vector3(1, 1, 1);

	//Set Collision box
	MinExtent = Position + MODELMINPOINT;
	MaxExtent = Position + MODELMAXPOINT;

	//Set Forward direction to rotation
	ForwardDirection = EulerAnglesToDirection(Vector3(PITCH, YAW, 0));

	//Get a cross product of the forward direction using up 
	RightDirecton = VectorCrossProduct(Vector3(0, 1, 0), ForwardDirection);

	//Normalise this, allows the player to look up and still go right
	RightDirecton = VectorNormalized(RightDirecton);

	//Get the cross product of the forward direction and right direction 
	UpDirection = VectorCrossProduct(ForwardDirection, RightDirecton);

	//If up is true reduce pitch by sensertivity
	if (UP == true)
	{
		PITCH -= Sensertivity;
	}

	//If Down is true increease the pitch by sensertivity
	if (DOWN == true)
	{
		PITCH += Sensertivity;
	}

	//If Left is true increase yaw by sensertivity
	if (LEFT == true)
	{
		YAW += Sensertivity;
	}

	//If Right is true decrease yaw by seensertivity
	if (RIGHT == true)
	{
		YAW -= Sensertivity;
	}
	
	//Clamp Pitch between 89.99 to -89.99 Stops camera from inverting
 PITCH = clamp(PITCH, 89.99, -89.99);

 //Clamp Sensertivity
	Sensertivity = clamp(Sensertivity, 2, -0.5);

//Move Foward
	if (W == true)
	{
		Force += ForwardDirection * 100;
	}

	//Movebackwards
	if (S == true)
	{
		Force -= ForwardDirection * 100;
	}

	//Move Right 
	if (A == true)
	{
		Force -= RightDirecton * 100;
	}

	//Move Left
	if (D == true)
	{
		Force += RightDirecton * 100;
}	

	//Dampen Velocity
	if (X == true)
	{
		Velocity /= 1.01f;
		//		Velocity = DivideVector(Velocity, );
	}

	//Move Up
	if (SPACE == true)
	{
		Force += UpDirection * 100;
	}

	//Move Down
	if (CONTROL == true)
	{
		Force -= UpDirection * 100;
	}

	//Increase Sensertivity
	if (PLUS == true)
	{
		Sensertivity += 0.05f;
	}

	//Decrease Senerstivity
	if (MINUS == true)
	{
		Sensertivity -= 0.05f;
	}
	//Create Temporay gun
	initGun GunTemp;

	//Set Origin Transformation
	GunTemp.Position = Position;
	GunTemp.Rotation = Rotation;

	//Set Forward Direciton
	GunTemp.ForwardDirection = ForwardDirection;

	//Set offset
	GunTemp.offsetdirection = "Left";

	//Set Draw Texture
	GunTemp.DrawTexture = DrawTexture;

	//Set Deltatime
	objGunLeft.DeltaTime = DeltaTime;

	//Setup Left Gun to gun gump
	objGunLeft.Setup(GunTemp);


	//Set Origin Transformation
	GunTemp.Position = Position;
	GunTemp.Rotation = Rotation;

	//Set Forward Direciton
	GunTemp.ForwardDirection = ForwardDirection;

	//Set offset
	GunTemp.offsetdirection = "Right";

	//Set Draw Texture
	GunTemp.DrawTexture = DrawTexture;

	//Set Deltatime
	objGunRight.DeltaTime = DeltaTime;

	//Setup Right Gun to gun gump
	objGunRight.Setup(GunTemp);

	//Update Guns
	objGunLeft.Update();
	objGunRight.Update();

	//If f is true
	if (F == true)
	{	
		//if left gun can fire
		if (objGunLeft.BulletWait >= 0.25)
		{
			//set bullet wait to 0
			objGunLeft.BulletWait = 0;

			//If gun fired
			if (objGunLeft.Fire() == true)
			{
				//Increase shots by 1
				Shots += 1;
			}
	
		}
		
		// If Right Gun Can Fire
		if (objGunRight.BulletWait >= 0.25)
		{
	
			//Set bullet wait to 0
			objGunRight.BulletWait = 0;

			//If Gun fired
			if (objGunRight.Fire() == true)
			{

				//Increases shot by one
				Shots += 1;
			}

			//Sets F to flase
			F = false;


		}

}
	//Updates guns 
	objGunLeft.Update();
	objGunRight.Update();
	
	//Dampens the velocity
	Velocity /= 1.01f;

	//Sets accleration 
	Acceleration = Force / Mass;

	//Increases velocity by Accleration * Delta time
	Velocity += Acceleration *DeltaTime;
	
	//Increeass positon by Velocity * Delta time
	Position += Velocity* DeltaTime;

	//Sets rotation to pitch and yaw
	Rotation = Vector3(PITCH,YAW,0);

	//Sets force
	Force = Vector3(0, 0, 0);	
}

//Deconstruct Player
Player::~Player()
{
	Mass = NULL;
	PITCH = NULL;
	YAW = NULL;
	Sensertivity = NULL;
	Health = NULL;
	DeltaTime = NULL;
	Shots = NULL;
	W = NULL;
	A = NULL;
	S = NULL;
	D = NULL;
	Q = NULL;
	E = NULL;
	LEFT = NULL;
	RIGHT = NULL;
	UP = NULL;
	DOWN = NULL;
	SHIFT = NULL;
	CONTROL = NULL;
	SPACE = NULL;
	X = NULL;
	PLUS = NULL;
	MINUS = NULL;
	F = NULL;

}
