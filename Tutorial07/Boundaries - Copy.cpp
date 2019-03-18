#include "Boundaries.h"



Boundaries::Boundaries()
{
}

void Boundaries::Setup(XMFLOAT3 Position, XMFLOAT3 Rotation, XMFLOAT3 Scale, float colourR, float colourG, float colourB, int targetchance, bool leftWall, bool rightWall, bool frontwall, bool backwall, bool roof)
{

	transform.Setup(Position, Rotation, Scale, colourR, colourG, colourG);
	LeftWall = leftWall;
	RightWall = rightWall;
	BackWall = backwall;
	FrontWall = frontwall;
	Roof = roof;
}


void Boundaries::Update()
{
	if (BackWall == true)
	{
		objBackWall.Setup(XMFLOAT3(transform.Position.x - 5.5f, transform.Position.y + 5.5, transform.Position.z), XMFLOAT3(0, 0, 0), XMFLOAT3(0.5, 5, 5), transform.Red, transform.Green, transform.Blue);
		objBackWall.CollisionBox.Update(objBackWall);
		objBackWall.Draw();
	}
	if (FrontWall == true)
	{
		objFrontWall.Setup(XMFLOAT3(transform.Position.x + 5.5f, transform.Position.y + 5.5, transform.Position.z), XMFLOAT3(0, 0, 0), XMFLOAT3(0.5, 5, 5), transform.Red, transform.Green, transform.Blue);
		objFrontWall.Draw();
	}
	if (LeftWall == true)
	{
		objLeftWall.Setup(XMFLOAT3(transform.Position.x, transform.Position.y + 5.5, transform.Position.z + 5.5f), XMFLOAT3(0, 0, 0), XMFLOAT3(5, 5, 0.5), transform.Red, transform.Green, transform.Blue);
		objLeftWall.Draw();
	}
	if (RightWall == true)
	{
		objRightWall.Setup(XMFLOAT3(transform.Position.x, transform.Position.y + 5.5, transform.Position.z - 5.5f), XMFLOAT3(0, 0, 0), XMFLOAT3(5, 5, 0.5), transform.Red, transform.Green, transform.Blue);
		objRightWall.Draw();
	}
	if (Roof == true)
	{
		objRoof.Setup(XMFLOAT3(transform.Position.x, transform.Position.y + 10.5f, transform.Position.z), XMFLOAT3(0, 0, 0), XMFLOAT3(5, 0.5, 5),  transform.Red, transform.Green, transform.Blue);
		objRoof.Draw();
	}
	transform.Draw();
}
Boundaries::~Boundaries()
{
}
