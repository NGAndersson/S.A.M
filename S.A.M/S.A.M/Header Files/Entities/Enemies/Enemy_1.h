#ifndef ENEMY_1_H
#define ENEMY_1_H
#include "Enemy.h"

class Enemy_1
{
	//Functions
private:
protected:
public:
	Enemy_1();
	Enemy_1(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Enemy(SoundManager, MapWidth, MapLength, Position) {}
	~Enemy_1();
	void Update(double time);
	void Destroy();

	//Attributes
private:
protected:
public:

}

#endif