#include "Corridor.h"


//Corridor Constructor Setting Default Valeus
Corridor::Corridor()
{
	FloorLength = 2;
	objBoundaries = new Boundaries[50];
}

//Setup function, quick way to generate a corridor
void Corridor::Setup(corridorsInit Init)
{
 //Create Game Object Initilaiser
	GameObjectInit Temp;

	//Setting Temp Values to init values
	Temp.position = Init.Position;
	Temp.scale = Init.Scale;
	Temp.rotation = Init.Rotation;
	Temp.ColourB = Init.colourB;
	Temp.ColourG = Init.colourG;
	Temp.ColourR = Init.colourR;
	Temp.DrawTexture = Init.DrawTexture;

	//Calling Game Object Setup
    Setup(Temp);

	//Random Number for Turrets, not implemented
	int RandomNumber = 50;
	
	
	//Creates a random number between 0 and 49 to be used by boundaries to create targets
	int RandomNumber2 = rand() % 50;;

    //Clamps floor length to ensure a corridor is made
	Init.floorLength = clamp(Init.floorLength, 50, 2);

	//Loop going through the boundaries 
	for (int i = 0; i < FloorLength; i++)
	{
		//Forces target to be false
		objBoundaries[i].TARGET = false;
	}

	//Setting floor length 
	FloorLength = Init.floorLength;


	//All Corridors Start from the origin position and then create in the intended direction

	//If Corridor is going down
	if (Init.CorridorDirection == "Down")
	{

		//Loop through boundaries
		for (int i = 0; i < FloorLength; i++)
		{
			
			//If First block
			if (i == 0)
			{
				
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Transformation
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;
				
				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
			    corridortemp.turretchance= RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;

				//Setting Draw TExtures
				corridortemp.DrawTexture = Init.DrawTexture; 
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
			
			//Else if its the last block
			 else if (i == FloorLength -1)
			{
				 
				 //Creating Temporay Boundarie
				BoundariesInit corridortemp;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
			    corridortemp.turretchance= RandomNumber2;

				 //Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and decreases the y by 10
				corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[i - 1].Position.y - 10.0f, objBoundaries[0].Position.z);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Wall Variables
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;

				//Setting Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else Create the middle
			else
			{
				
				//Creating Temporay Boundarie
				BoundariesInit corridortemp;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and decreases the y by 10
				corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[i - 1].Position.y - 10.0f, objBoundaries[0].Position.z);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;


			   //Setting Wall Variables
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = true;
				corridortemp.backwall = true;
				corridortemp.floor = false;
				corridortemp.roof = false;

				//Setting Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
		}
	}
	
	//If Corridor is going Up
	if (Init.CorridorDirection == "Up"	)
	{

		//Loop through boundaries
		for (int i = 0; i < FloorLength; i++)
		{
			
			//If First BLock
			if (i == 0)
			{
				
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Transformation
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;

				//Setting Draw Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
		    
			//Else if its the last block
			else if (i == FloorLength -1)
			{
				
				//Creating Temporay boundary
				BoundariesInit corridortemp;
				
				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and Adding y by 10
				corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[i - 1].Position.y + 10.0f, objBoundaries[0].Position.z);
				
				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;

				//Setting Draw Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else creatre the middle
			else
			{
				
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and Adding y by 10
				corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[i - 1].Position.y + 10.0f, objBoundaries[0].Position.z);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

			
			  //Setting Wall Variables
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = true;
				corridortemp.backwall = true;
				corridortemp.floor = false;
				corridortemp.roof = false;
				
				//Setting Draw Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
		}
	}

	//If Corridor Is Going Right
	if (Init.CorridorDirection == "Right")
	{
		
		//Loop through boundaries
		for (int i = 0; i < FloorLength; i++)
		{

			//If First BLock
			if (i == 0)
			{
				
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Transformation
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;

				//Setting Draw TExtures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else if its the last block
			else if (i == FloorLength -1)
			{
				
				//Creating Temporay boundary
				BoundariesInit corridortemp;
			
				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and Subtracting z by 10
				corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[0].Position.y, objBoundaries[i - 1].Position.z - 10.0f);
				
				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;

				//Setting Draw Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else creatre the middle
			else
			{
			
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and Subtracting z by 10
				corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[0].Position.y, objBoundaries[i - 1].Position.z - 10.0f);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = false;
				corridortemp.rightWall = false;
				corridortemp.frontwall = true;
				corridortemp.backwall = true;
				corridortemp.floor = true;
				corridortemp.roof = true;

				//Setting Draw Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
		}
	}

	//If Corridor is going Left
	if (Init.CorridorDirection == "Left")
	{

		//Loop through boundaries
		for (int i = 0; i < FloorLength; i++)
		{

			//If First block
			if (i == 0)
			{

				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Transformation
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;

				//Setting Draw TExtures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
				}

			    //Else if its the last block
		     	else if (i == FloorLength -1)
				{

					//Creating Temporay Boundarie
					BoundariesInit corridortemp;

					//Setting Target And Turret Chance
					corridortemp.targetchance = RandomNumber;
					corridortemp.turretchance = RandomNumber2;

					//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and adds z by 10
					corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[0].Position.y, objBoundaries[i - 1].Position.z + 10.0f);
				
					//Setting Rotation And Scale
					corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
					corridortemp.Scale = Vector3(5, 0.5, 5);

					//Setting Colour
					corridortemp.colourR = Init.colourR;
					corridortemp.colourG = Init.colourG;
					corridortemp.colourB = Init.colourB;

					//Setting Wall Variables
					corridortemp.leftWall = Init.LastBlock.leftWall;
					corridortemp.rightWall = Init.LastBlock.rightWall;
					corridortemp.frontwall = Init.LastBlock.frontwall;
					corridortemp.backwall = Init.LastBlock.backwall;
					corridortemp.floor = Init.LastBlock.floor;
					corridortemp.roof = Init.LastBlock.roof;

					//Setting Textures
					corridortemp.DrawTexture = Init.DrawTexture;
					corridortemp.TargetTexture = Init.TargetTexture;

					//Sets objBoundarie to be corridortemp
					objBoundaries[i].Setup(corridortemp);
				}
			
			//Else Create the Middle
				else
				{
					//Creating Temporay Boundarie
					BoundariesInit corridortemp;

					//Setting Target And Turret Chance
					corridortemp.targetchance = RandomNumber;
					corridortemp.turretchance = RandomNumber2;

					//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and adds z by 10
					corridortemp.Position = Vector3(objBoundaries[0].Position.x, objBoundaries[0].Position.y, objBoundaries[i - 1].Position.z + 10.0f);

					//Setting Rotation And Scale
					corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
					corridortemp.Scale = Vector3(5, 0.5, 5);

					//Setting Colour
					corridortemp.colourR = Init.colourR;
					corridortemp.colourG = Init.colourG;
					corridortemp.colourB = Init.colourB;

					//Setting Wall Variables
					corridortemp.leftWall = false;
					corridortemp.rightWall = false;
					corridortemp.frontwall = true;
					corridortemp.backwall = true;
					corridortemp.floor = true;
					corridortemp.roof = true;

					//Setting Textures
					corridortemp.DrawTexture = Init.DrawTexture;
					corridortemp.TargetTexture = Init.TargetTexture;

					//Sets objBoundarie to be corridortemp
					objBoundaries[i].Setup(corridortemp);
				}
			}
		}
	
	//If Corridor is going Backward
	if (Init.CorridorDirection == "Backward")
	{
	
		//Loops through boundaries
		for (int i = 0; i < FloorLength; i++)
		{

			//If First block
			if (i == 0)
			{
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Transformation
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;

				//Setting Draw TExtures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
			
			//Else if its the last block
			else if (i == FloorLength -1)
			{

				//Creating Temporay Boundarie
				BoundariesInit corridortemp;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and decreases the x by 10
				corridortemp.Position = Vector3(objBoundaries[i - 1].Position.x - 10.0f, objBoundaries[i - 1].Position.y, objBoundaries[i - 1].Position.z);
			
				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Wall Variables
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;

				//Setting Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else Create the middle 
			else
			{
				
				//Creating Temporay Boundarie
				BoundariesInit corridortemp;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and decreases the x by 10
				corridortemp.Position = Vector3(objBoundaries[i - 1].Position.x - 10.0f, objBoundaries[i - 1].Position.y, objBoundaries[i - 1].Position.z);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Wall Variables
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = false;
				corridortemp.backwall = false;
				corridortemp.floor = true;
				corridortemp.roof = true;

				//Setting Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
		}
	}

	//If Corridor is going forward 
	if (Init.CorridorDirection == "Forward")
	{

		//Loop through boundaries
		for (int i = 0; i < FloorLength; i++)
		{

			//If First block
			if (i == 0)
			{
				//Creating Temporay boundary
				BoundariesInit corridortemp;

				//Setting Transformation
				corridortemp.Position = Vector3(Position.x, Position.y, Position.z);
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Wall Variables
				corridortemp.leftWall = Init.FirstBlock.leftWall;
				corridortemp.rightWall = Init.FirstBlock.rightWall;
				corridortemp.frontwall = Init.FirstBlock.frontwall;
				corridortemp.backwall = Init.FirstBlock.backwall;
				corridortemp.floor = Init.FirstBlock.floor;
				corridortemp.roof = Init.FirstBlock.roof;

				//Setting Draw TExtures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else if its the last block
			else if (i == FloorLength - 1)
			{
				//Creating Temporay Boundarie
				BoundariesInit corridortemp;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and increases the x by 10
				corridortemp.Position = Vector3(objBoundaries[i - 1].Position.x +10.0f, objBoundaries[i - 1].Position.y, objBoundaries[i - 1].Position.z);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Wall Variables
				corridortemp.leftWall = Init.LastBlock.leftWall;
				corridortemp.rightWall = Init.LastBlock.rightWall;
				corridortemp.frontwall = Init.LastBlock.frontwall;
				corridortemp.backwall = Init.LastBlock.backwall;
				corridortemp.floor = Init.LastBlock.floor;
				corridortemp.roof = Init.LastBlock.roof;

				//Setting Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}

			//Else create the middle
			else
			{
				//Creating Temporay Boundarie
				BoundariesInit corridortemp;

				//Setting Target And Turret Chance
				corridortemp.targetchance = RandomNumber;
				corridortemp.turretchance = RandomNumber2;

				//Setting Position, Gets the first block postion Ands sets the XYZ, then gets the the block before it and increases the x by 10
				corridortemp.Position = Vector3(objBoundaries[i - 1].Position.x + 10.0f, objBoundaries[i - 1].Position.y, objBoundaries[i - 1].Position.z);

				//Setting Rotation And Scale
				corridortemp.Rotation = Vector3(Rotation.x, Rotation.y, Rotation.z);
				corridortemp.Scale = Vector3(5, 0.5, 5);

				//Setting Colour
				corridortemp.colourR = Init.colourR;
				corridortemp.colourG = Init.colourG;
				corridortemp.colourB = Init.colourB;

				//Setting Wall Variables
				corridortemp.leftWall = true;
				corridortemp.rightWall = true;
				corridortemp.frontwall = false;
				corridortemp.backwall = false;
				corridortemp.floor = true;
				corridortemp.roof = true;

				//Setting Textures
				corridortemp.DrawTexture = Init.DrawTexture;
				corridortemp.TargetTexture = Init.TargetTexture;

				//Sets objBoundarie to be corridortemp
				objBoundaries[i].Setup(corridortemp);
			}
		}
	}
}

//Setup Function for boundaries game object
void Corridor::Setup(GameObjectInit Init)
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
void Corridor::Update()
{
	//Loop through the boundaries
	for (int i = 0; i < FloorLength; i++)
	{

		//Call Boundaires update
		objBoundaries[i].Update();
	}
}

//Deconstruct Corridor
Corridor::~Corridor()
{
	FloorLength = NULL;
	objBoundaries = NULL;
	delete objBoundaries;
}
