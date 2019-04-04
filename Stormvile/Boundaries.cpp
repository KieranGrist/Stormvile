#include "Boundaries.h"


//Boundaries Constructor Setting Default Values
Boundaries::Boundaries()
{
	 TURRET = false; 
	 turretchance =0; 
	 targetchance =0; 
	 FrontWall = false;
	 BackWall = false; 
	 LeftWall = false; 
	 RightWall = false;
	 Roof = false;
	 Floor = false; 
	 TARGET = false;
}

//Setup Function, quick way to set values 
void Boundaries::Setup(BoundariesInit Init)
{
	//Create Game Object Initialiser
	GameObjectInit Temp;

	//Setting Temp values to init values
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	Temp.DrawTexture = Init.DrawTexture; 

	//Calling Game Object Setup
	Setup(Temp);

	//Setting Walls, roof and floor bools
	LeftWall = Init.leftWall;
	RightWall = Init.rightWall;
	BackWall = Init.backwall;
	FrontWall = Init.frontwall;
	Roof = Init.roof;
	Floor = Init.floor;

	//Setting Turret Chance
	turretchance = Init.turretchance;

	//Setting Target Chance
	targetchance = Init.targetchance;

	//Position is the origin point, the walls will generate around this origin point

	//If Backwall is true create the backwall
	if (BackWall == true)
	{
		
		//Setting Position, first get the Position XYZ, then minus the x by 5.5, and add 5.5 to the y 
		Temp.position = Vector3(Position.x - 5.5f, Position.y + 5.5f, Position.z);

		//Setting Rotation to Origin values
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);

		//Forcing scale to be 0.5,5,5
		Temp.scale = Vector3(0.5, 5, 5);

		//Set colours
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;

		//Setup back wall to temp
		objBackWall.Setup(Temp);
	}

	//If frontwall is true create the front wall 
	if (FrontWall == true)
	{
		
		//Setting Position, first get the position XYZ,then add 5.5 to the x and y 
		Temp.position = Vector3(Position.x + 5.5f, Position.y + 5.5f, Position.z);

		//Setting Rotation to Origin Values
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);

		//Forcing Scale to be 0.5,5,5
		Temp.scale = Vector3(0.5, 5, 5);

		//Set Colours
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;

		//Setup front wall to temp
		objFrontWall.Setup(Temp);
	}

	//If Leftwall is true create the left wall
	if (LeftWall == true)
	{
		
		//Set Position, first get the position, then add 5.5 to y and z
		Temp.position = Vector3(Position.x, Position.y + 5.5f, Position.z + 5.5f);

		//Set Rotation to Origin
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);

		//Force Scale to be 5,5,0.5f
		Temp.scale = Vector3(5.0f, 5.0f, 0.5f);

		//Set Colours
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;

		//Setup left wall to temp
		objLeftWall.Setup(Temp);
	}

	//If Rightwall is true create Right Wall
	if (RightWall == true)
	{

		//Set Position, first get the position, then add 5.5 to y, and minus 5.5 to the z
		Temp.position = Vector3(Position.x, Position.y + 5.5f, Position.z - 5.5f);

		//Set Rotation to Origin
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);

		//Force Scale to be 5,5,0
		Temp.scale = Vector3(5.0f, 5.0f, 0.5f);

		//Set Colours
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;

		//Setup Right wall to temp
		objRightWall.Setup(Temp);
	}
	
	//If Roof is true create Roof
	if (Roof == true)
	{
		
		//Set Posotion,first get the position, then add 10.5 to y
		Temp.position = Vector3(Position.x, Position.y + 10.5f, Position.z);

		//Set Rotation to Origin
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);

		//Force Scale to be 5,0.5,5
		Temp.scale = Vector3(5.0f, 0.5f, 5.0f);

		//Set Colours
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;

		//Set roof to temp
		objRoof.Setup(Temp);
	}

	//If floor is true create floor
	if (Floor == true)
	{

		//Set Position to origin position
		Temp.position = Vector3(Position.x, Position.y, Position.z);

		//Set Rotation to origin
		Temp.rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);

		//Set Scale to 5,0.5,5
		Temp.scale = Vector3(5.0f, 0.5f, 5.0f);

		//Set Colour
		Temp.ColourR = Red;
		Temp.ColourG = Green;
		Temp.ColourB = Blue;

		//Set Floor to temp
		objFloor.Setup(Temp);
	}
	
	bool TargetSpawned = false; //Variable to check if the target has been spawned
	int RandomNumber = rand() % 100; //Number between 0, 100, this number will be checked against the target chance
	int TimesRan = 0; //Variable to check number of times the loop has been ran

	//If Random Number is Less then or equal to the target chance, spawn a target
	if (RandomNumber <= targetchance)
	{
		//Run this loop while the target has not been spawned
		while (TargetSpawned == false)
		{
			TimesRan++;

			//If Ran more then 1000 times stop loop
			if (TimesRan >= 1000)
			{
				//Set Target spawned to true
				TargetSpawned = true;
			}

			int Wall = rand() % 6; //Generates a number between 0 and 5, this number will represent a game object

//Switch statement, switches between walls values
			switch (Wall)
			{

				//Floor Case
			case 0:

				//If Floor is true spawn a target here
				if (Floor == true)
				{
					//Creating target setup
					targetInit TargetTemp;

					//Setting Target position to floor position
					TargetTemp.Position = objFloor.Position;

					//Adding 1.5 to y
					TargetTemp.Position.y += 1.5f;

					//Set Rotation to 0,0,0
					TargetTemp.Rotation = Vector3(0, 0, 0);

					//Set Scale to 1,1,1
					TargetTemp.Scale = Vector3(1, 1, 1);

					//Set Target Helath to 100
					TargetTemp.Health = 100;

					//Set Colours
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;

					//Set Target Texture
					TargetTemp.DrawTexture = Init.TargetTexture;

					//Set Target to true
					TARGET = true;

					//Set objtarget to be temp
					objTarget.Setup(TargetTemp);

					//Set Target spawned to be true
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}

				//Roof Casse
			case 1:

				// If Roof is true spawn a target here
				if (Roof == true)
				{

					//Creating target setup
					targetInit TargetTemp;

					//Set position to objroof position 
					TargetTemp.Position = objRoof.Position;

					//Minus y by 1.5f
					TargetTemp.Position.y -= 1.5f;

					//Set rotation to 0,0,0
					TargetTemp.Rotation = Vector3(0, 0, 0);

					//Set Scale to be 1,1,1
					TargetTemp.Scale = Vector3(1, 1, 1);

					//Set Health to 100
					TargetTemp.Health = 100;

					//Set Colours
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;

					//Set Draw Texture to Target Texture
					TargetTemp.DrawTexture = Init.TargetTexture;

					//Set Target to true
					TARGET = true;

					//Set target to Temp
					objTarget.Setup(TargetTemp);

					//Set Target spawned to true
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}

				//Leftwall Case
			case 2:

				//If left wall is true spawn target here
				if (LeftWall == true)
				{

					//Creating target setup
					targetInit TargetTemp;

					//Set position to objroof position 
					TargetTemp.Position = objLeftWall.Position;

					//Minus z by 1.5f
					TargetTemp.Position.z -= 1.5f;

					//Set rotation to 0,0,0
					TargetTemp.Rotation = Vector3(0, 0, 0);

					//Set Scale to be 1,1,1
					TargetTemp.Scale = Vector3(1, 1, 1);

					//Set Health to 100
					TargetTemp.Health = 100;

					//Set Colours
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;

					//Set Draw Texture to Target Texture
					TargetTemp.DrawTexture = Init.TargetTexture;

					//Set Target to true
					TARGET = true;

					//Set target to Temp
					objTarget.Setup(TargetTemp);

					//Set Target spawned to true
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 3:
				if (RightWall == true)
				{

					//Creating target setup
					targetInit TargetTemp;

					//Set position to objroof position 
					TargetTemp.Position = objRightWall.Position;

					//Add z by 1.5f
					TargetTemp.Position.z += 1.5f;

					//Set rotation to 0,0,0
					TargetTemp.Rotation = Vector3(0, 0, 0);

					//Set Scale to be 1,1,1
					TargetTemp.Scale = Vector3(1, 1, 1);

					//Set Health to 100
					TargetTemp.Health = 100;

					//Set Colours
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;

					//Set Draw Texture to Target Texture
					TargetTemp.DrawTexture = Init.TargetTexture;

					//Set Target to true
					TARGET = true;

					//Set target to Temp
					objTarget.Setup(TargetTemp);

					//Set Target spawned to true
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 4:
				if (FrontWall == true)
				{

					//Creating target setup
					targetInit TargetTemp;

					//Set position to objroof position 
					TargetTemp.Position = objFrontWall.Position;

					//Subtracting x by 1.5f
					TargetTemp.Position.x -= 1.5f;

					//Set rotation to 0,0,0
					TargetTemp.Rotation = Vector3(0, 0, 0);

					//Set Scale to be 1,1,1
					TargetTemp.Scale = Vector3(1, 1, 1);

					//Set Health to 100
					TargetTemp.Health = 100;

					//Set Colours
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;

					//Set Draw Texture to Target Texture
					TargetTemp.DrawTexture = Init.TargetTexture;

					//Set Target to true
					TARGET = true;

					//Set target to Temp
					objTarget.Setup(TargetTemp);

					//Set Target spawned to true
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			case 5:
				if (BackWall == true)
				{

					//Creating target setup
					targetInit TargetTemp;

					//Set position to objroof position 
					TargetTemp.Position = objBackWall.Position;

					//Adding x by 1.5f
					TargetTemp.Position.x += 1.5f;

					//Set rotation to 0,0,0
					TargetTemp.Rotation = Vector3(0, 0, 0);

					//Set Scale to be 1,1,1
					TargetTemp.Scale = Vector3(1, 1, 1);

					//Set Health to 100
					TargetTemp.Health = 100;

					//Set Colours
					TargetTemp.colourB = 1;
					TargetTemp.colourG = 1;
					TargetTemp.colourR = 1;

					//Set Draw Texture to Target Texture
					TargetTemp.DrawTexture = Init.TargetTexture;

					//Set Target to true
					TARGET = true;

					//Set target to Temp
					objTarget.Setup(TargetTemp);

					//Set Target spawned to true
					TargetSpawned = true;
					break;
				}
				else
				{
					break;
				}
			default:

				//Set Target spawned to true
				TargetSpawned = false;
				break;

			}
		}
	}
}

//Setup Function for boundaries game object
void Boundaries::Setup(GameObjectInit Init)
{
	Position = Init.position;
	Rotation = Init.rotation;
	Scale = Init.scale;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
}


//Update Function
void Boundaries::Update()
{
	
	//If backwall is true update backwall
	if (BackWall == true)
	{
		
		//Update Backwall
		objBackWall.Update();

		//Reset Min extent as update overrides it
		objBackWall.MinExtent = VectorSub(objBackWall.Position, Vector3(0.5, 5, 5));

		//Reset Max extent as update overrides it
		objBackWall.MaxExtent = VectorAdd(objBackWall.Position, Vector3(0.5, 5, 5));		
	}

	//If frontwall is true update frontwall
	if (FrontWall == true)
	{
		
		//Update FrontWall
		objFrontWall.Update();

		//Reset Min extent as update overrides it
		objFrontWall.MinExtent = VectorSub(objFrontWall.Position, Vector3(0.5, 5, 5));

		//Reset Max extent as update overrides it
		objFrontWall.MaxExtent = VectorAdd(objFrontWall.Position, Vector3(0.5, 5, 5));

	}

	//If Leftwall is true update leftwall
	if (LeftWall == true)
	{
		
		//Update Leftwall
		objLeftWall.Update();

		//Reset Min extent as update overrides it
		objLeftWall.MinExtent = VectorSub(objLeftWall.Position, Vector3(5.0f, 5.0f, 0.5f));

		//Reset Max extent as update overrides it
		objLeftWall.MaxExtent = VectorAdd(objLeftWall.Position, Vector3(5.0f, 5.0f, 0.5f));
	}

	//if RightWall is true update RightWall
	if (RightWall == true)
	{

		//Update RightWall
		objRightWall.Update();

		//Reset Min extent as update overrides it
		objRightWall.MinExtent = VectorSub(objRightWall.Position, Vector3(5.0f, 5.0f, 0.5f));

		//Reset Max extent as update overrides it
		objRightWall.MaxExtent = VectorAdd(objRightWall.Position, Vector3(5.0f, 5.0f, 0.5f));
	}

	//If Roof is true update Roof
	if (Roof == true)
	{

		//Update Roof
		objRoof.Update();

		//Reset Min extent as update overrides it
		objRoof.MinExtent = VectorSub(objRoof.Position, Vector3(5.0f, 0.5f, 5.0f));

		//Reset Max extent as update overrides it
		objRoof.MaxExtent = VectorAdd(objRoof.Position, Vector3(5.0f, 0.5f, 5.0f));
	}

	//If Floor is true update Floor
	if (Floor == true)
	{

		//Update Floor
		objFloor.Update();

		//Reset Min extent as update overrides it
		objFloor.MinExtent = VectorSub(objFloor.Position, Vector3(5.0f, 0.5f, 5.0f));

		//Reset Max extent as update overrides it
		objFloor.MaxExtent = VectorAdd(objFloor.Position, Vector3(5.0f, 0.5f, 5.0f));
	}

	//If Targeat is true Update target
	if (TARGET == true)
	{

		//Check the target is still alive
		if (objTarget.Health <= 0)
		{

			//Set target to false
			TARGET = false;
		}

		//Update Target
		objTarget.Update();
	}
}

//Deconstruct Boundaries
Boundaries::~Boundaries()
{
	TURRET = NULL;
	turretchance = NULL;
	targetchance = NULL;
	FrontWall = NULL;
	BackWall = NULL;
	LeftWall = NULL;
	RightWall = NULL;
	Roof = NULL;
	Floor = NULL;
	TARGET = NULL;
}
