#include "CollisionBox.h"

//CollisionBox Constructor Setting Default Values
CollisionBox::CollisionBox()
{
	MinExtent = Vector3(0, 0, 0);
	MaxExtent = Vector3(0, 0, 0);
}

//Setup Function,quick way to set values
void CollisionBox::Setup(Vector3 MinExt, Vector3 MaxExt)
{
	MinExtent = MinExt;
	MaxExtent = MaxExt;
}

//Function to get Top of AABB
float CollisionBox::GetTop()
{
	return MaxExtent.y;
}

//Function to get Bottom of AABB
float CollisionBox::GetBottom()
{
	return MinExtent.y;
}

//Function to get Left of AABB
float CollisionBox::GetLeft()
{
	return MinExtent.x;
}

//Function to get Right of AABB
float CollisionBox::GetRight()
{
	return MaxExtent.x;
}

//Function to get Front of AABB
float CollisionBox::GetFront()
{
	return MaxExtent.z;
}

//Function to get Back of AABB
float CollisionBox::GetBack()
{
	return MinExtent.z;
}

//Function to check for AABB Collision
bool CollisionBox::Intersects(CollisionBox Box1, CollisionBox Box2)
{

	//Rejection check
	return !(Box2.GetLeft() > Box1.GetRight()
		|| Box2.GetRight() < Box1.GetLeft()
		|| Box2.GetTop() < Box1.GetBottom()
		|| Box2.GetBottom() > Box1.GetTop()
		|| Box2.GetBack() > Box1.GetFront()
		|| Box2.GetFront() < Box1.GetBack());
}

//Deconstructor for collision box
CollisionBox::~CollisionBox()
{
}
