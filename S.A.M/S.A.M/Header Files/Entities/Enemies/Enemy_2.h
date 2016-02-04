#ifndef ENEMY_2_H
#define ENEMY_2_H
#include "Enemy.h"

class Enemy_2 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_2();
	Enemy_2(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Enemy(SoundManager, MapWidth, MapLength, Position) {}
	~Enemy_2();
	void Update(double time);
	void Destroyed();

	//Attributes
private:
protected:
public:

};

#endif