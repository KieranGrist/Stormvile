#include "Gun.h"


//Gun Constructor
Gun::Gun()
{
	objbulletlist = new Bullet[50]; //Creates 50 bullets
	BulletWait = 0;
	DrawTexture = nullptr;
	DeltaTime = 0;
}

//Setup function for gun
void Gun::Setup(initGun Init)
{
	//Loops through bullets
	for (int i = 0; i < 50; i++)
	{
		//Sets bullet id
		objbulletlist[i].BulletID = i;
	}
	//Sets gun postion and rotation to origin
	Position = Init.Position;
	Rotation = Init.Rotation;

	//Sets scale
	Scale = Vector3(1, 1, 1);

	//Sets Draw Texture
	DrawTexture = Init.DrawTexture;

	//If Gun is to the left
	if (Init.offsetdirection == "Left")
	{
		//Find the cross product or forward direction 
		Vector3 Left = VectorCrossProduct(Vector3(0, 1, 0), Init.ForwardDirection);

		//Normalise the result 
		Left = VectorNormalized(Left);

		//Subtractrs Postion by Left
		Position -=  Left;
	}

	//If Gun is to the right
	if (Init.offsetdirection == "Right")
	{
		//Find the cross product or forward direction 
		Vector3 Right = VectorCrossProduct(Vector3(0, 1, 0), Init.ForwardDirection);
		
		//Normalise the result 
		Right = VectorNormalized(Right);

		//Adds Postion by Left
		Position += Right;
	}
}

//Setup using gameobject
void Gun::Setup(GameObjectInit Init)
{
	Position = Init.position;
	Rotation = Init.rotation;
	Scale = Init.scale;
	Red = Init.ColourR;
	Green = Init.ColourG;
	Blue = Init.ColourB;
	DrawTexture = Init.DrawTexture;
}
//Fire Bullet
bool Gun::Fire()
{
	//Loop through bullets
	for (int i = 0; i < 50; i++)
	{ 
		//If bullet is false
		if (objbulletlist[i].Alive == false)
		{

			//Create a temporay bullet
			bulletInit TempBullet;
			
			//Set Draw texture
			TempBullet.DrawTexture = DrawTexture;;

			//Set Bullet Origin
			TempBullet.GunPos = Position;
			TempBullet.GunRot = Rotation;

			//Setup Bullet
			objbulletlist[i].Setup(TempBullet);

			//Force it to be alive
			objbulletlist[i].Alive = true;

			//Force it to reset the timeout
			objbulletlist[i].TimeOutDestructor = 0;
			
			//End loop
			i = 60;
			
			//Return bullet fired
			return true;
		}
	}
	
	//Return bullet not fired
	return false;
}
void Gun::Update()
{
	//Adds Delta time to bullet wait
	BulletWait += DeltaTime;

	//Loop through the bullets
	for (int i = 0; i < 50; i++)
	{

		//If Bullet is alive
		if (objbulletlist[i].Alive == true)
		{

			//Update Bullet
			objbulletlist[i].Update();

			//Set Delta Time
			objbulletlist[i].DeltaTime = DeltaTime;

			//If Timeout Destructor Is More then or equal to 5
			if (objbulletlist[i].TimeOutDestructor >= 5)
			{
				//Kill bullet
				objbulletlist[i].Alive = false;
			}
		}
	}
}
Gun::~Gun()
{
	objbulletlist = NULL; //Creates 50 bullets
	delete objbulletlist;
	BulletWait = NULL;
	DrawTexture = nullptr;
	DeltaTime = NULL;
}
