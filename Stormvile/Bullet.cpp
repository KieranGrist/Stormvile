#include "Bullet.h"


//Bullet Constructor
Bullet::Bullet()
{
	 TimeOutDestructor = 0;
	 Force = Vector3(); 
	 Acceleration = Vector3();
	 Velocity = Vector3();
	 ForwardDirection = Vector3(); 
	 Pitch = 0; 
	 Yaw =0;
	 Mass =0;
	 Alive = false; 
	 DeltaTime =0; 
	 BulletID = 0; 
}

//Bullet Setup
void Bullet::Setup(bulletInit Init)
{
	//SetTimeout to 0
	TimeOutDestructor = 0;

	//Setscale to 0.1,0.1,0.1
	Scale =  Vector3(0.1,0.1, 0.1);

	//Set Draw texture
	DrawTexture = Init.DrawTexture;

	//Set Position to gun postion
	Position = Init.GunPos;

	//Create a random number between 0 and 254
	int myRand = rand() % 255;

	//Sets Red
	Red = (myRand > 128) ? 255 : 0;//@Ternary operator (condition) ? (if true) : (if false)
	
	//Sets Green
	Green = (myRand <= 128) ? 255 : 0;

	//Sets Blue
	Blue = 0;

	//Sets Pitch to gun rotation x
	Pitch = Init.GunRot.x;

	//Sets aw to gun rotation y
	Yaw = Init.GunRot.y;

	//Set Forward direction
	ForwardDirection = VectorMaths::EulerAnglesToDirection(Vector3(Pitch, Yaw, 0));

	//Sets Alive to true
	Alive = true;

	//Applies a force of 1000 in the forward direction
	Force = MultiplyVector(ForwardDirection, 1000);

	//Sets velocity to 0,0,0
	Velocity = Vector3(0, 0, 0);

	//Sets Acceleration to 0,0,0
	Acceleration = Vector3(0, 0, 0);
}

//Updates Bullet
void Bullet::Update()
{
	//Adds Delta time to Timeout
	TimeOutDestructor += DeltaTime;

	//Updates MinExtent, Set to 1,1,1 to give a higher chance of hitting targets
	MinExtent = VectorSub(Position, Vector3(1, 1, 1));
	
	//Updates MaxExtent, Set to 1,1,1 to give a higher chance of hitting targets
	MaxExtent = VectorAdd(Position, Vector3(1, 1, 1));

	//Sets mass to 1
	Mass = 1.0f;

	//Sets Accleration to be Force /Mass
	Acceleration =Force/ Mass;

	//Adds Accleration * Delta time to Velocity
	Velocity += Acceleration*DeltaTime;

	//Adds Velocity * Delta Time to 
	Position += Velocity*DeltaTime;

	//Draws bullet
	Draw();
}

//Deconstruct Bullet
Bullet::~Bullet()
{
}
