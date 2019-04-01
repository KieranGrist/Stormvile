#include "CollisionBox.h"




void CollisionBox::Setup(Vector3 MinExt, Vector3 MaxExt)
{
	MinExtent = MinExt;
	MaxExtent = MaxExt;
}

CollisionBox::CollisionBox()
{
	MinExtent = Vector3(0, 0, 0);
	MaxExtent = Vector3(0, 0, 0);
}
float CollisionBox::GetTop()
{
	return MaxExtent.y;
}
float CollisionBox::GetBottom()
{
	return MinExtent.y;
}
float CollisionBox::GetLeft()
{
	return MinExtent.x;
}
float CollisionBox::GetRight()
{
	return MaxExtent.x;
}
float CollisionBox::GetFront()
{
	return MaxExtent.z;
}
float CollisionBox::GetBack()
{
	return MinExtent.z;
}
 bool CollisionBox::Intersects(CollisionBox Box1, CollisionBox Box2)
{
	 Vector3 Box1Half = (Box1.MaxExtent - Box1.MinExtent) * 0.5f;// + Box1.MinExtent;
	 Vector3 Box2Half = (Box2.MaxExtent - Box2.MinExtent) * 0.5f;// + Box2.MinExtent;													 //Get Direction Between the two boxes + edges
	 Vector3 Box1Centre = Box1Half + Box1.MinExtent;
	 Vector3 Box2Centre = Box2Half + Box2.MinExtent;
	 //Colliding to the Right


	 if (abs(Box1Centre.x - Box2Centre.x) > (Box1Half.x + Box2Half.x))
	 {
		 return false;
	 }
	 if (abs(Box1Centre.y - Box2Centre.y) >(Box1Half.y + Box2Half.y))
	 {
		 return false;
	 }

	 if (abs(Box1Centre.z - Box2Centre.z) >(Box1Half.z + Box2Half.z))
	 {
		 return false;
	 }
	 return true;
}

CollisionBox::~CollisionBox()
{
}
