#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Enemy : public Entity
{
	//Functions
private:
protected:
public:
	Enemy();
	Enemy(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Entity(SoundManager, MapWidth, MapLength, Position) {}
	~Enemy();
	void Update(double time);
	void Destroyed();

	//Attributes
private:
protected:
public:

};

#endif