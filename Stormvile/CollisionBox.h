//File Name : CollisionBox.h
#pragma once
#include "VectorMaths.h"
class CollisionBox : public VectorMaths
{
public:
	Vector3 MinExtent, MaxExtent;
	Vector3 MinPoints, MaxPoints;
	void SetBox(Vector3 Min, Vector3 Max)
	{
		MinPoints = Min;
		MaxPoints = Max;
	}
	void UpdateBox(Vector3 Position)
	{
		Setup(Position - MinPoints, Position + MaxPoints);
	}
	virtual void Setup(Vector3 MinEx, Vector3 MaxExtent);
	CollisionBox();
	virtual float GetTop();
	virtual float GetBottom();
	virtual float GetLeft();
	virtual float GetRight();
	virtual float GetFront();
	virtual float GetBack();
	 static bool Intersects(CollisionBox BOX1, CollisionBox BOX2);
	~CollisionBox();
};

