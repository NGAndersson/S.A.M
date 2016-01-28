#ifndef ENTITY_H
#define ENTITY_H
//Temporary include
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>

using namespace DirectX
#include "SoundManager.h"

#define MOVEMENTSPEED 0.05f

//#include "EntityManager.h"
class  Entity
{
	//----------------------------Functions----------------------------------------
public:
	 virtual void Update(double time) = 0;

	 virtual void Initialize(SoundManager& SoundManager, int MapWidth, int MapLenght) = 0;

	 virtual void Destoyed() = 0;

	 //Get set 
	 virtual XMFLOAT3 GetPosition()
	 {
		 return m_position;
	 }

	 virtual void SetPosition(XMFLOAT3 NewPos)
	 {
		 m_position = NewPos;
	 }

	 virtual XMMATRIX GetRotation()
	 {
		 return m_rotation;
	 }

	 virtual BoundingBox GetBoundingBox()
	 {
		 return m_entityBox;
	 }

	//----------------------------Attributes----------------------------------------
protected:
	//Modelhandler

	//SoundManager
	 SoundManager* m_soundManager;
	 //Position // Rotation
	 XMFLOAT3 m_position;
	 XMMATRIX m_rotation;

	 //BoundingBox
	 BoundingBox m_entityBox;
	 int m_mapWidth, m_mapLenght;
};
#endif // ! ENTITY

