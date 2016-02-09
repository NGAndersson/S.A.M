#ifndef ENEMY_H
#define ENEMY_H
#include "Entities/Entity.h"

class Enemy : public Entity
{
	//Functions
private:
protected:
public:
	Enemy() {}
	Enemy(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health) : Entity(SoundManager, MapWidth, MapLength, Position, Scale, Health) {
		XMVECTOR _rotzAxis{ 0,0,1,0 };
		m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	}
	//~Enemy();
	virtual void Update(double time) = 0;
	virtual void Destroyed() = 0;

	//Attributes
private:
protected:
public:

};

#endif