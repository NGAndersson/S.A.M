#ifndef ENEMY_3_H
#define ENEMY_3_H
#include "Enemy.h"

class Enemy_3 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_3();
	Enemy_3(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Enemy(SoundManager, MapWidth, MapLength, Position) {}
	~Enemy_3();
	void Update(double time);
	void Destroyed();

	//Attributes
private:
protected:
public:

};

#endif