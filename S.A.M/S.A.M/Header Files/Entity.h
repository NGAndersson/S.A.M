#ifndef ENTITY_H
#define ENTITY_H
//Temporary include
#include <DirectXCollision.h>

using namespace DirectX

#include "SoundManager.h"
//#include "EntityManager.h"
class  Entity
{
	//Destructor and Constructor
	virtual Entity() = 0;
	virtual ~Entity() = 0;
	//Uppdate screens
	 virtual void Uppdate(int CurrentScreen) = 0;
	//Initializing the screen manager
	 virtual void Initialize() = 0;

	 //Get set 
	 virtual int GetPosition();
	 virtual void SetPosition(int NewPos);
	 virtual BoundingBox GetBoundingBox();

	//----------------------------Attributes----------------------------------------
private:
	//Modelhandler

	//SoundManager
	 SoundManager mSoundManager;

	 //Position
	 int mPosition;

	 //BoundingBox
	 BoundingBox mBoundingBox;
	 
};
#endif // ! ENTITY

