#include "Room.h"



Room::Room()
{
	ObjBoundaries = new Boundaries[100];
}

void Room::Setup(roomInit Init)
{

	//GameObjectInit Temp;
	//Temp.position = Init.Position;
	//Temp.scale = Init.Scale;
	//Temp.rotation = Init.Rotation;
	//Temp.ColourB = Init.colourB;
	//Temp.ColourG = Init.colourG;
	//Temp.ColourR = Init.colourR;
	//Temp.DrawTexture = Init.DrawTexture;
	//GameObject::Setup(Temp);

	//BoundariesInit BoundTemp;
	//BoundTemp.Position = XMFLOAT3(Position.x , Position.y, Position.z);
	//BoundTemp.Rotation;
	//BoundTemp.Scale = XMFLOAT3(1, 1, 1);
	//BoundTemp.colourR;
	//BoundTemp.colourG;
	//BoundTemp.colourB;
	//BoundTemp.targetchance = 0;//50;
	//BoundTemp.turretchance;
	//BoundTemp.leftWall = false;
	//BoundTemp.rightWall = false;
	//BoundTemp.frontwall = true;
	//BoundTemp.backwall = true;
	//BoundTemp.roof = true;
	//BoundTemp.floor = true;
	//BoundTemp.DrawTexture = Init.DrawTexture;
	//BoundTemp.TurretTexture = Init.TargetTexture;
	//BoundTemp.TargetTexture = Init.TargetTexture;
	//Entrance.Setup(BoundTemp);
	//Position.z += 10;
	//int i = 0;
	//for (int X = 0; X < 100; X+=10)
	//{
	//	for (int Z = 0; Z < 100; Z += 10)
	//	{
	//		BoundTemp.Position = XMFLOAT3(Position.x+X,Position.y,Position.z +Z);
	//		BoundTemp.Rotation;
	//		BoundTemp.Scale= XMFLOAT3(1,1,1);
	//		BoundTemp.colourR;
	//		BoundTemp.colourG; 
	//		BoundTemp.colourB;
	//		BoundTemp.targetchance =0;//50;
	//		BoundTemp.turretchance;
	//		BoundTemp.leftWall = false;
	//		BoundTemp.rightWall = false;
	//		BoundTemp.frontwall = false;
	//		BoundTemp.backwall = false;
	//		BoundTemp.roof = true;
	//		BoundTemp.floor = true;
	//		BoundTemp.DrawTexture = Init.DrawTexture;
	//		BoundTemp.TurretTexture = Init.TargetTexture;
	//		BoundTemp.TargetTexture = Init.TargetTexture;

	//
	//		//Switch going through the edges of the room
	//		switch (i)
	//		{
	//		case 0:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 1:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 2:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 3:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 4:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 5:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 6:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 7:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 8:
	//			BoundTemp.backwall = true;
	//			break;
	//		case 9:
	//			BoundTemp.leftWall = true;
	//			BoundTemp.backwall = true;
	//			break;
	//		case 10:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 19:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 20:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 29:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 30:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 39:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 40:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 49:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 50:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 59:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 60:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 69:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 70:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 79:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 80:
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 89:
	//			BoundTemp.leftWall = true;
	//			break;
	//		case 90:
	//			BoundTemp.frontwall = true;
	//			BoundTemp.rightWall = true;
	//			break;
	//		case 91:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 92:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 93:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 94:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 95:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 96:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 97:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 98:
	//			BoundTemp.frontwall = true;
	//			break;
	//		case 99:
	//			BoundTemp.frontwall = true;
	//			BoundTemp.leftWall = true;
	//			break;
	//		default:
	//			break;
	//		}
	//		ObjBoundaries[i].Setup(BoundTemp);
	//		i++;
	//	}
	//} 

}
void Room::Setup(GameObjectInit Init)
{
	Setup(Init);
}
void Room::Update()
{
	//for (int i = 0; i < 100; i++)
	//{
	//	ObjBoundaries[i].Update();

	//}
	//Entrance.Update();
}


Room::~Room()
{
}
