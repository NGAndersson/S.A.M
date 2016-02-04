#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Enemy : public Entity
{
	//Functions
private:
protected:
public:
	Enemy() {}
	Enemy(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Entity(SoundManager, MapWidth, MapLength, Position) {}
	//~Enemy();
	virtual void Update(double time) = 0;
	virtual void Destroyed() = 0;

	//Attributes
private:
protected:
public:

};

#endif