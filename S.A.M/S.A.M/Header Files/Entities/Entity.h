#ifndef ENTITY_H
#define ENTITY_H
//Temporary include
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include "Gamelogic\Input.h"
using namespace DirectX;
#include "Audio/SoundManager.h"
#include <Graphics/Light.h>

#define MOVEMENTSPEEDX 0.3f / 9.80f // Divided by screen Width Hardcoded MOTHERFUCKER :)

#define MOVEMENTSPEEDZ 0.3f / 7.20f // Divided by screen Height Hardcoded
enum HandlerIndex { PLAYER, BULLET1, BULLET2, BULLET3, BULLET4, BULLET5, BULLET6, ENEMY1, ENEMY2, ENEMY3, ENEMY4 };
class Entity
{
	//----------------------------Functions----------------------------------------
public:
	Entity() 
	{
		m_mapWidth = 0;
		m_mapLength = 0;
		m_entityWidth = 0;
		m_fireTime = 0;
		m_health = 0;
		m_score = 0;
		m_speed = 0;
	}
	virtual ~Entity() {}
	Entity(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
	{
		m_soundManager = SoundManager;
		m_mapLength = MapLength;
		m_mapWidth = MapWidth;
		m_position = Position;
		m_scale = Scale;
		m_entityWidth = 5.0f;

		m_fireTime = 0;
		m_speed = 0;

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

	 virtual double GetFireTime() { return m_fireTime; }

	 virtual void SetFireTime(double NewTime) { m_fireTime = NewTime; }

	 virtual int GetInvulnerable(){ return m_invulnerable; }

	 virtual float GetSpeed() { return m_speed; }

	 virtual Light* GetLight() { return m_light; }

	 virtual int GetPatternNr() { return m_patternNr; }

	 virtual void SetPatternNr(int NrOfPatterns) { m_patternNr = NrOfPatterns; }

	//----------------------------Attributes----------------------------------------
protected:
	//Modelhandler

	//SoundManager
	 SoundManager* m_soundManager = nullptr;
	 //Position // Rotation
	 XMFLOAT3 m_position;
	 XMMATRIX m_rotation;
	 XMFLOAT3 m_scale;

	 //BoundingBox
	 BoundingBox m_entityBox;
	 int m_mapWidth, m_mapLength;
	 float m_entityWidth;
	 double m_fireTime;
	 //When entities are to be deleted
	 bool m_delete = false;
	 bool m_invulnerable = false;
	 Light* m_light = nullptr;
	 int m_patternNr = 0;

	 int m_health;
	 int m_score;
	 float m_speed;
};
#endif // ! ENTITY