#pragma once
#include "CollisionBox.h"
struct SimpleVertex
{
	Vector3 Pos;
	Vector2 Tex;
	Vector3 Normal;
	Vector4 color;

};
class Model : public CollisionBox
{
public:
	SimpleVertex * ObjectVertex = NULL;
	WORD * ObjectIndices = NULL;
	ID3D11Buffer* ObjectVertexBuffer = nullptr;
	ID3D11Buffer* ObjectIndexBuffer = nullptr;
	int IndexAmmount;
	void CreateModel(std::string path);
	Model()
	{
	}
	
	~Model()
	{
	}

};

