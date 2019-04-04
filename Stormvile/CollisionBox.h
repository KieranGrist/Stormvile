//File Name : CollisionBox.h
#pragma once
#include "VectorMaths.h"
//Collision Box Class, used to detect if two objects are colliding
class CollisionBox : public VectorMaths
{
public:
	Vector3 MinExtent; //MinExtent Of Box
	Vector3 MaxExtent; //MaxExtent Of Box
	virtual void Setup(Vector3 MinEx, Vector3 MaxExtent); //Setup Box
	CollisionBox(); 
	virtual float GetTop(); //Get Top Of Box
	virtual float GetBottom(); //Get Bottom of Box
	virtual float GetLeft(); //Get Left Of Box
	virtual float GetRight(); //Get Right Of Box
	virtual float GetFront(); //Get Front Of Box
	virtual float GetBack(); //Get Back Of Box
	 static bool Intersects(CollisionBox BOX1, CollisionBox BOX2); //Foward Decleration of Intersects function
	~CollisionBox();
};

