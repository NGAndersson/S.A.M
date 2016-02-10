#ifndef ENTITY_H
#define ENTITY_H
//Temporary include
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include "Gamelogic\Input.h"
using namespace DirectX;
#include "Audio/SoundManager.h"

#define MOVEMENTSPEEDX 0.3f / 16.40f // Divided by screen Width Hardcoded MOTHERFUCKER :)

#define MOVEMENTSPEEDZ 0.3f / 7.20f // Divided by screen Height Hardcoded
enum HandlerIndex { PLAYER, BULLET1, BULLET2, BULLET3, BULLET4, BULLET5, BULLET6, ENEMY1, ENEMY2, ENEMY3, ENEMY4 };
class Entity
{
	//----------------------------Functions----------------------------------------
public:
	Entity() {}
	~Entity() {}
	Entity(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
	{
		m_soundManager = SoundManager;
		m_mapLength = MapLength;
		m_mapWidth = MapWidth;
		m_position = Position;
		m_scale = Scale;
		m_entityWidth = 5.0f;

		m_score = 0;
		m_health = Health;
		m_entityBox.Center = Position;
		m_entityBox.Extents = XMFLOAT3(1.0f, 1.0f, 1.0f);
	}

	virtual void Update(double time) = 0;

	virtual void Destroyed(double time) = 0;

	 //Get set 
	 virtual XMFLOAT3 GetPosition(){return m_position;}

	 virtual void SetPosition(XMFLOAT3 newPos) { m_position = newPos; }

	 virtual XMMATRIX GetRotation(){ return m_rotation; }

	 virtual XMFLOAT3 GetScale() { return m_scale; }

	 virtual void SetScale(XMFLOAT3 newScale) { m_scale = newScale; }

	 virtual BoundingBox GetBoundingBox() { return m_entityBox; }

	 virtual bool GetDelete() { return m_delete; }

	 virtual void SetDelete(bool b) { m_delete = b; }

	 virtual int GetHealth(){return m_health;}

	 virtual void AddHealth(int change){ m_health += change;}

	 virtual int GetScore() { return m_score; }

	//----------------------------Attributes----------------------------------------
protected:
	//Modelhandler

	//SoundManager
	 SoundManager* m_soundManager;
	 //Position // Rotation
	 XMFLOAT3 m_position;
	 XMMATRIX m_rotation;
	 XMFLOAT3 m_scale;

	 //BoundingBox
	 BoundingBox m_entityBox;
	 int m_mapWidth, m_mapLength;
	 float m_entityWidth;

	 //When entities are to be deleted
	 bool m_delete = false;

	 int m_health;
	 int m_score;
};
#endif // ! ENTITY
